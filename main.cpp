#include <Arduino.h>
// #include <SPIFlash.h>
#include <SerialFlash.h>
#include <SPI.h>
// #include <EEPROM.h>

#define fileSize 128000   //Sevenish hours of data
#define threshold 100   //will be bin number from ADC
#define FLASH_CHIP_SELECT1 8   //chip select pin number for flash chip #1
#define FLASH_CHIP_SELECT2 9   //chip select pin number for flash chip #2
#define ADC_CHIP_SELECT 10     //chip select pin number for ADC

SerialFlashFile file;
// SerialFlashChip SerialFlash;
SerialFlashChip SerialFlash2;

// FUNCTION: Retrieve the digitized signal from the photodiode signal
uint16_t getPhotodiode() {
  uint16_t photodiode16;
  // REVISIT maxSpeed
  SPI.beginTransaction(SPISettings(20000,MSBFIRST,SPI_MODE3)); //SPISettings(maxSpeed,dataOrder,dataMode)
  digitalWrite(ADC_CHIP_SELECT,LOW); // set Slave Select pin 10 to low to select chip
  photodiode16 = SPI.transfer16(0x00);
  digitalWrite(ADC_CHIP_SELECT,HIGH); // set Slave Select pin 10 to high to de-select chip
  SPI.endTransaction();
  return photodiode16;
}

void setup() {
  //pin 8 for Slave Select    //connected to pin 1 of flash mem 1 - output from master
  //pin 9 for Slave Select    //connected to pin 1 of flash mem 2 - output from master
  pinMode(ADC_CHIP_SELECT, OUTPUT);   //pin 10 for Slave Select    //connected to pin 3 on ADC (ADC_CS) - input to master
  pinMode(A2,INPUT);
  //pin 11 for Master Output Slave Input (MOSI) - sends data to flash memory
  //pin 12 for Master Input Slave Output (MISO) - receives data from ADC //connects to pin 6 on ADC
  //pin 13 for Serial Clock (SCK) - output from master //connects to pin 5 on ADC
  SPI.begin();  
  SerialFlash.begin(FLASH_CHIP_SELECT1);
  // SerialFlash2.begin(FLASH_CHIP_SELECT2);
  Serial.begin(9600);
  delay(5000);
  // char filename[10] = getFilename(); 
  // TODO: Function that scans for existing files and generates unused name
  // General filename format: "data###.txt" (11 char)
  Serial.println("start");
  char filename[11] = "Test.bin";
  if(!SerialFlash.exists(filename)) {
    Serial.print("Creating file: ");
    Serial.println(filename);
    SerialFlash.createErasable(filename, fileSize);
  }
  
  file = SerialFlash.open(filename);   // Attempt opening file
  
  int openAttempts = 1;
  while(!file) {
    Serial.print("Attempt ");
    Serial.print(openAttempts);
    Serial.println(" - File open failed.");
    file = SerialFlash.open(filename);   // Re-attempt opening existing file
    if(openAttempts >= 20){
      // Something is quite wrong. This shouldn't require retrys, let alone 20.
      Serial.println("Excessive open attempts - check hardware connections, capacity, filenames.");
      Serial.println("Recommend terminating run.");
      break; // Just. Stop trying.
    } else {
      openAttempts++; // Add to attempt counter and retry
    }
  }
}

void loop() {
    // General format: 50 measurements at 50Hz, then remaining minute downtime. 
    // Repeat for full observing run.
    int looptime1 = millis();
    for(int i = 0; i < 50; i++) {
        uint32_t sampletime1 = millis();
        uint16_t photodiodeSignal = analogRead(A2);
        file.write(&sampletime1,4);
        file.write(&photodiodeSignal,2);
        //Serial.print(photodiodeSignal);
        // Serial.print(", ");
        uint32_t sampletime2 = millis();
        delay(200-(sampletime2-sampletime1)); // Enforce 50Hz sample rate, ie. one sample per 20ms.  
    }
    Serial.println("");
    int looptime2 = millis();
    delay(6000-(looptime2-looptime1)); // Enforce run frequency, ie. one sample run per minute.  
}

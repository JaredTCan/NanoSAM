#include <Arduino.h>
// #include <SPIFlash.h>
#include <SerialFlash.h>
#include <SPI.h>
#include <String.h>
// #include <EEPROM.h>

#define fileSize 128000   //Sevenish hours of data
#define threshold 100   //will be bin number from ADC
#define FLASH_CHIP_SELECT1 8   //chip select pin number for flash chip #1
#define FLASH_CHIP_SELECT2 9   //chip select pin number for flash chip #2
#define ADC_CHIP_SELECT 10     //chip select pin number for ADC

SerialFlashFile file;
// SerialFlashChip SerialFlash;
SerialFlashChip SerialFlash2;

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
  int fileNum = 0;
  String stringFileNum = String(fileNum);
  String filename = String("diode" + stringFileNum + ".bin");
  char filenameChar[16];
  filename.toCharArray(filenameChar,16);
  
  while(SerialFlash.exists(filenameChar) && fileNum < 999) 
  {
    fileNum++;
    String stringFileNum = String(fileNum);
    filename = String("diode" + stringFileNum + ".bin");
    filename.toCharArray(filenameChar,16);
  }
  Serial.print("Creating file: ");
  Serial.println(filenameChar);
  SerialFlash.createErasable(filenameChar, fileSize);
  
  file = SerialFlash.open(filenameChar);   // Attempt opening file
}

void loop() {
    // General format: 50 measurements at 50Hz, then remaining minute downtime. 
    // Repeat for full observing run.
    int looptime1 = millis();
    uint16_t photodiodeSignal = analogRead(A2);
    file.write(&looptime1,4);
    file.write(&photodiodeSignal,2);
    Serial.print(photodiodeSignal);
    Serial.println("");
    int looptime2 = millis();
    delay(500-(looptime2-looptime1)); // Test frequency is ~1 sample/s  
}
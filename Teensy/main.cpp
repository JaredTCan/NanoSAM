#include <Arduino.h>
// #include <SPIFlash.h>
#include <SerialFlash.h>
#include <SPI.h>

#define fileSize 1 //REVISIT
#define threshold 100 //will be bin number from ADC
#define FLASH_CHIP_SELECT1 8
#define FLASH_CHIP_SELECT2 9
#define ADC_CHIP_SELECT 10
SerialFlashFile file;
SerialFlashChip SerialFlash;
SerialFlashChip SerialFlash2;

void setup() {
  // put your setup code here, to run once:
  // Measured photodiode voltage (should be in binary - int variable?)
  // pinMode(8, OUTPUT);    //pin 8 for Slave Select    //connected to pin 1 of flash mem 1 - output from master
  // pinMode(9, OUTPUT);    //pin 9 for Slave Select    //connected to pin 1 of flash mem 2 - output from master
  pinMode(10, OUTPUT);   //pin 10 for Slave Select    //connected to pin 3 on ADC (ADC_CS) - input to master
  // pinMode(11, PIN_SPI_MOSI); //pin 11 for Master Output Slave Input (MOSI) - sends data to flash memory
  // pinMode(12, PIN_SPI_MISO); //pin 12 for Master Input Slave Output (MISO) - receives data from ADC //connects to pin 6 on ADC
  // pinMode(13, PIN_SPI_SCK);  //pin 13 for Serial Clock (SCK) - output from master //connects to pin 5 on ADC

  SPI.begin();
  SerialFlash.begin(FLASH_CHIP_SELECT1);
  // SerialFlash2.begin(FLASH_CHIP_SELECT2);
  Serial.begin(9600);
  SerialFlash.create("Test", fileSize);
  file = SerialFlash.open("Test");
  if (!file) {
    //Error flash file open
    Serial.println("Didn't work");
    return;
  }

  boolean dataCapture = true; //setting condition to continue taking data until threshold is reached
  while (dataCapture){ //will run until dataCapture is false
    uint16_t val16 = getADC();

    Serial.println(val16);
    // SCIENCE DATA STORAGE
    // write to NOR flash chips via SerialFlash
    file.write(&val16, 2);

    if (val16 <= threshold){ //if photodiode voltage is less than or equal to threshold then set dataCapture to false (ends while loop)
      dataCapture = false;
    }
  }

  while (!Serial.available());
  char buf[fileSize];
  file.read(buf,fileSize);
  Serial.println(buf);

}

void loop() {
//nothing
}

uint16_t getADC(){
  uint16_t photodiode16;
  SPI.beginTransaction(SPISettings(50,MSBFIRST,SPI_MODE3)); //SPISettings(maxSpeed,dataOrder,dataMode)
  digitalWrite(ADC_CHIP_SELECT,LOW); // set Slave Select pin 10 to low to select chip
  photodiode16 = SPI.transfer16(0x00);
  digitalWrite(ADC_CHIP_SELECT,HIGH); // set Slave Select pin 10 to high to de-select chip
  SPI.endTransaction();
  return photodiode16;
}

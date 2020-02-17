#include <Arduino.h>
// #include <SPIFlash.h>
#include <SerialFlash.h>
#include <SPI.h>

#define fileSize 256   //REVISIT
#define threshold 100   //will be bin number from ADC
#define FLASH_CHIP_SELECT1 8   //chip select pin number for flash chip #1
#define FLASH_CHIP_SELECT2 9   //chip select pin number for flash chip #2
#define ADC_CHIP_SELECT 10     //chip select pin number for ADC
SerialFlashFile file;
// SerialFlashChip SerialFlash;
SerialFlashChip SerialFlash2;
uint32_t Variable10 = 0; 

/*uint16_t getADC(){
  uint16_t photodiode16;
  SPI.beginTransaction(SPISettings(50,MSBFIRST,SPI_MODE3)); //SPISettings(maxSpeed,dataOrder,dataMode)
  digitalWrite(ADC_CHIP_SELECT,LOW); // set Slave Select pin 10 to low to select chip
  photodiode16 = SPI.transfer16(0x00);
  digitalWrite(ADC_CHIP_SELECT,HIGH); // set Slave Select pin 10 to high to de-select chip
  SPI.endTransaction();
  return photodiode16;
}
*/

void setup() {
  //pin 8 for Slave Select    //connected to pin 1 of flash mem 1 - output from master
  //pin 9 for Slave Select    //connected to pin 1 of flash mem 2 - output from master
  pinMode(10, OUTPUT);   //pin 10 for Slave Select    //connected to pin 3 on ADC (ADC_CS) - input to master
  //pin 11 for Master Output Slave Input (MOSI) - sends data to flash memory
  //pin 12 for Master Input Slave Output (MISO) - receives data from ADC //connects to pin 6 on ADC
  //pin 13 for Serial Clock (SCK) - output from master //connects to pin 5 on ADC
  
  SPI.begin();  
  SerialFlash.begin(FLASH_CHIP_SELECT1);
  // SerialFlash2.begin(FLASH_CHIP_SELECT2);
  Serial.begin(9600);
  delay(5000);
  Serial.println("Line 37");
  SerialFlash.createErasable("Test.bin", fileSize);
  file = SerialFlash.open("Test.bin");   //checks to see if file can open or not
  
  if (!file) {
    //Error flash file open
    Serial.println("Didn't work");
  }
  file.erase();
  boolean dataCapture = true; //setting condition to continue taking data until threshold is reached
  while (dataCapture){ //will run until dataCapture is false
    //uint16_t val16 = getADC();
    uint16_t val16 = 0x5453;

    // Serial.println(val16);

     //write 16-bit (2 byte) binary photodiode voltage to file

    if (!file.write(&val16, 1)){ //if photodiode voltage is less than or equal to threshold then set dataCapture to false (ends while loop)
      dataCapture = false;
    }
    Variable10++;
  }

  Serial.println("Not in while loop");
  
  // while (!Serial.available()); //waits for serial connection to be active
  char buf[10];          //character array the size of fileSize
  file.seek(0);
  if(!file.read(buf,10)){
    Serial.println("Didn't read anything");
  }     //read data from file
  Serial.println(file.size());
  Serial.println(file.position());
  for (int i=0; i<10; i++){
    Serial.println(buf[i]);
  }
  // Serial.printf("buf:%.*s\n",(int)sizeof(buf),buf);         //serial print data to make sure it is being stored in file
  Serial.println("After buf");
}

void loop() {
//Serial.println("Hello");
delay(1000);
Serial.println(Variable10);
delay(1000);
}


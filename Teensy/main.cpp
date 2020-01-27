#include <Arduino.h>
// #include <SPIFlash.h>
#include <SerialFlash.h>
#include <SPI.h>

void setup() {
// put your setup code here, to run once:
// Initialize variables (data integers, etc)
  // Photodiode threshold voltage
    double threshold = 1.435; //volts  // int/double threshold_voltage - from testing with photodiode
  // Photodiode input voltage - *input*
    double input_voltage = 3.30; //volts //double - required input voltage for photodiode  
  // Measured photodiode voltage (should be in binary - int variable?)
    int photodiode;
  // Packetized data (?) - *Data Transmission*
    int data_out;
  // Initialize pin modes (digital, analog, Tx, Rx, etc)

  SPI.begin();
  pinMode(8, OUTPUT);    //pin 8 for Slave Select    //connected to pin 1 of flash mem 1 - output from master
  pinMode(9, OUTPUT);    //pin 9 for Slave Select    //connected to pin 1 of flash mem 2 - output from master
  pinMode(10, INPUT);   //pin 10 for Slave Select    //connected to pin 3 on ADC (ADC_CS) - input to master
  pinMode(11, PIN_SPI_MOSI); //pin 11 for Master Output Slave Input (MOSI) - sends data to flash memory
  pinMode(12, PIN_SPI_MISO); //pin 12 for Master Input Slave Output (MISO) - receives data from ADC //connects to pin 6 on ADC
  pinMode(13, PIN_SPI_SCK);  //pin 13 for Serial Clock (SCK) - output from master //connects to pin 5 on ADC
}

void loop() {
boolean dataCapture = true; //setting condition to continue taking data until threshold is reached
while (dataCapture){ //will run until dataCapture is false
photodiode = digitalWrite(10,LOW); //reading digital data incoming in pin 10 and storing it in variable "photodiode"

if (photodiode <= threshold); //if photodiode voltage is less than or equal to threshold then set dataCapture to false (ends while loop)
  dataCapture = false;

// SCIENCE DATA STORAGE
// write to NOR flash chips via SPI
SPI.beginTransaction(SPISettings(8000000,MSBFIRST,SPI_MODE3)); //SPISettings(maxSpeed,dataOrder,dataMode)
digitalWrite(8,LOW); // set Slave Select pin 8 to low to select chip
SPI.transfer(photodiode); //write data to chip
digitalWrite(8,HIGH); // set Slave Select pin 8 to high to de-select chip
SPI.endTransaction();

// DATA TRANSMISSION
    // Take stored data from NOR flash memory
  // Serial.print()
    // packetize data for transmission (???????)
    // Serial data output to laptop
}
}
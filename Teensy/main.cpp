#include <Arduino.h>
// #include <SPIFlash.h>
#include <SerialFlash.h>
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  // Initialize variables (data integers, etc)
      // Photodiode threshold voltage - *Sun-scanning control*
      double threshold = 1.435; //volts  // int/double threshold_voltage - from testing with photodiode
      // Photodiode input voltage - *input*
      double input_voltage = 3.30; //volts //double - required input voltage for photodiode  
      // Packetized data (?) - *Data Transmission*
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
// put your main code here, to run repeatedly:
boolean dataCapture = true;
while (dataCapture)
{
// SUN-THRESHOLD MEASUREMENT
  // If photodiode voltage > threshold
    // do nothing (keep taking data)
    // remain pinMode(~,input)
  // else
    // stop taking data - break loop
    // dataCapture = false;
 
// SCIENCE DATA STORAGE (which pin inputs/outputs this data?)
    // take variable for digital data from ADC
    digitalWrite(10,LOW);

    // write to NOR flash chips (??????)
    SPI.beginTransaction(SPISettings(1000000,MSBFIRST,SPI_MODE3)); //SPISettings(maxSpeed,dataOrder,dataMode)
    digitalWrite(8,LOW); // set Slave Select pin 8 to low to select chip
    SPI.transfer(data); //write data to chip
    digitalWrite(8,HIGH); // set Slave Select pin 8 to high to de-select chip
    SPI.endTransaction();

// DATA TRANSMISSION
    // Take stored data from NOR flash memory
    
    // packetize data for transmission (???????)
    // Serial data output to laptop
}
}
#include <Arduino.h>

//int led = 13;

void setup() {
  // put your setup code here, to run once:
  // Initialize variables (data integers, etc)
      // Photodiode threshold voltage - *Sun-scanning control*
      double threshold = 1.435; //volts  // int/double threshold_voltage - from testing with photodiode
      // Photodiode input voltage - *input*
      double input_voltage = 3.30; //volts //double - required input voltage for photodiode  
      // Attitude data (simulated) - *Science Data Storage*
      // Packetized data (?) - *Data Transmission*
        //digitalWrite()
  // Initialize pin modes (digital, analog, Tx, Rx, etc)
  pinMode(2, INPUT); //pin for receiving data from ADC
  pinMode(1, CORE_TXD0_PIN); //pin for transmitting data to NOR Flash mem
  pinMode(8, PIN_SPI_SS);    //pin 8 for Slave Select    //connected to pin 1 of flash mem 1
  pinMode(9, PIN_SPI_SS);    //pin 9 for Slave Select    //connected to pin 1 of flash mem 2
  pinMode(10, PIN_SPI_SS);   //pin 10 for Slave Select   //connected to pin 3 on ADC (ADC_CS)
  pinMode(12, PIN_SPI_MISO); //pin 12 for Master Input Slave Output (MISO) - receives data from ADC //connects to pin 6 on ADC
  pinMode(13, PIN_SPI_SCK);  //pin 13 for Serial Clock (SCK) - output from master //connects to pin 5 on ADC
}

void loop() {
  // put your main code here, to run repeatedly:
boolean condish = true;
while (condish)
{
// SUN-THRESHOLD MEASUREMENT
    // If photodiode voltage > threshold
      // do nothing (keep taking data)
      // remain pinMode(~,input)
    // else
      // stop taking data - break loop
      // condish = false;
 
// SCIENCE DATA STORAGE (which pin inputs/outputs this data?)
    // take variable for digital data from ADC
    // take variable for simulated telemetry data (SPI from computer?)
    // append these datas together (??????)
    // write to NOR flash chips (??????)

// DATA TRANSMISSION
    // Take stored data from NOR flash memory
    // packetize data for transmission (???????)
    // Serial data output to simulated ground station
}
}
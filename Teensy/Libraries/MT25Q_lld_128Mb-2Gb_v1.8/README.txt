About Serialize.h and Serialize.c:

The serial functionality of our test hardware is provided by a FPGA.  This device provides us with one status register to track the state of our FPGA., one control register, and two FIFO data buffers for reading and writing to the flash device.  

The control register (SPICR) allows us to tell our FPGA what mode of communication we wish to use, how many dummy cycles we need, whether to communicate with one, two, or four bits, and even what clock rate to use. Each bit of the register indicates what feature we have enabled and what we can expect as far as hardware behavior.  All writes to the SPICR change the behavior of our FPGA SPI engine.  We also have the ability to read this register to find out what is enabled or disabled.

The status register (SPISR) allows us to determine whether data is available to read from the read FIFO (SPIRDFIFO), and if all our output has been transmitted from the write FIFO (SPIWRFIFO).  Also available are bits indicating if a particular FIFO is full.

Serialize.C isolates the flash device control logic from the hardware requirements for communicating over a SPI bus.  All routines in this file will need to be re-written or provided in another file for use by the reference code routines in MT25Q.C.  You may prefer to cut-and-paste bits of the reference code into your own driver rather than adapt the reference code to your hardware requirements.
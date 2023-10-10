// IRtranmission.h
// Runs on LM4F120/TM4C123
// This code runs on PC5 GPIO output
// ECE319H tasks
// 1) Run transmitter with blind cycle synchronization
// Modified: 1/2/2023 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

// Simplex communication
// ECE319K Lab 9, use PC5 38 kHz modulated light output
// ECE319K Lab 9 hardware
// System xmt                        System rcv
//   PC5 --IR LED--> light >--IR sensor--- PC4
//   Gnd --------- not connected --------- Gnd
#include <stdint.h>
// standard ASCII symbols
#define STX  0x02
#define ETX  0x03
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

// Initialize GPIO on PC5
// Baud rate should divide evenly into 38,000
// for example baud rate of 2375 is 38,000/16
// 38 kHz, bit time is 421.05 us
// Lab 9
void IRtranmission_Init(uint32_t baud);

// output ASCII character to IR transmitter
// blind cycle synchronization
// in Lab 9 this will wait until tranmission is done
// start=0,bit0,bit1,bit2,bit2,bit4,bit5,bit6,bit7,stop=1
// 0 means 38 kHz pulse for 1 bit time
// 1 means no pulses for 1 bit time
void IRtranmission_OutChar(char data);




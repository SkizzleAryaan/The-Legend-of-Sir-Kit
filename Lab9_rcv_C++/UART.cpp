// UART.cpp
// Runs on TM4C123
// This code runs on UART0 with interrupts and a simple FIFO
// EE319K tasks
// 1) Convert to UART1 PC4 PC5
// 2) Implement the FIFO as a C++ class
// 3) Run transmitter with busy-wait synchronization (not used)
// 4) Run receiver with 1/2 full FIFO interrupt
// Modified: 1/2/2023 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly


/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2022
   Program 5.11 Section 5.6, Program 3.10

 Copyright 2022 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// starter code
// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

// EE319K Lab 9 hardware
// Simplex communication, this computer is receive only
// Use PC5 38 kHz modulated light output
// System xmt                        System rcv
//   PC5 --IR LED--> light >--IR sensor--- PC4
//   Gnd --------- not connected --------- Gnd
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#include "FIFO.h"
#include "UART.h"

#define PF1  (*((volatile uint32_t *)0x40025008))

extern "C" void DisableInterrupts(void); // Disable interrupts
extern "C" long StartCritical (void);    // previous I bit, disable interrupts
extern "C" void EndCritical(long sr);    // restore I bit to previous value
extern "C" void WaitForInterrupt(void);  // low power mode
extern "C" void EnableInterrupts(void);


extern "C" void UART1_Handler(void);
#define NVIC_EN0_INT6   0x00000040  // Interrupt 6 enable
Queue RxFifo; // static implementation of class
// Initialize UART1
// Baud rate is 115200 bits/sec
// Receiver interrupt on time out
// Transmitter uses busy wait
// Lab 9
void UART_Init(void){
  // write this
}


// input ASCII character from UART
// spin if RxFifo is empty
// Lab 9
char UART_InChar(void){
  // write this

  return 0; // replace this line
}
// Lab 9
bool UART_InStatus(void){
  // write this

  return false; // replace this line

}

// output ASCII character to UART
// busy-wait spin if hardware not ready
// Lab 9
// in Lab 9 this will never wait
void UART_OutChar(char data){
  // write this
}
// one thing has happened:
// hardware receiver timeout
// Lab 9
void UART1_Handler(void){
  PF1  ^= 0x02; // triple toggle debugging
  PF1  ^= 0x02;
 // write this
  
  PF1  ^= 0x02;
}
//------------UART_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until ETX is typed
//    or until max length of the string is reached.
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
void UART_InMessage(char *bufPt){
   // write this
// you may or may not need this function
}






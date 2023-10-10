// UART1.c
// Runs on LM4F120/TM4C123
// Use UART1 to implement bidirectional data transfer to and from 
// another microcontroller in Lab 9.  This time, interrupts and FIFOs
// are used.
// Daniel Valvano
// 1/2/2023

/* Lab solution, Do not post
 http://users.ece.utexas.edu/~valvano/
*/

// U1Rx (VCP receive) connected to PC4
// U1Tx (VCP transmit) connected to PC5
#include <stdint.h>
#include "Fifo.h"
#include "UART1.h"
#include "../inc/tm4c123gh6pm.h"

// Initialize UART1
// Baud rate is 2000 bits/sec 
void UART1_Init(void){
  // write this
	SYSCTL_RCGCUART_R |= 0x00000002;  // activate UART1
	
	while((SYSCTL_RCGCUART_R&0x02) != 0x2) {}; 
	
  SYSCTL_RCGCGPIO_R |= 0x00000004;  // activate port C
	
	while((SYSCTL_PRGPIO_R&0x04) != 0x4) {}; 

  UART1_CTL_R &= ~0x00000001;    // disable UART

  UART1_IBRD_R = 2500;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)

  UART1_FBRD_R = 0;     // FBRD = round(0.40278 * 64) = 26

  UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs

  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4

  GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1

  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;

  GPIO_PORTC_AMSEL_R &= ~0x30;   // disable analog on PC5-4
		
	NVIC_EN0_R |= 0x40; 
	
	UART1_IM_R |= 0x40; 
	
	NVIC_PRI1_R |= 0x400000; //(NVIC_PRI1_R & 0xFFFF00FF) | 0x4000;	
	
	UART1_CTL_R |= 0x00000301;     // enable UART
	
	//UART1_RIS_R |= 0x40; 
		
}

//------------UART1_InChar------------
// Wait for new input, 
// Use your FIFO, do not access UART1 hardware
// then return ASCII code
// Input: none
// Output: char read from UART
char UART1_InChar(void){
  // write this
   while((UART1_FR_R&0x0010) != 0);      // wait until RXFE is 0

  return(( char) UART1_DR_R & 0xFF);
}
//------------UART1_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until > is typed
//    or until max length of the string is reached.
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
void UART1_InMessage(char *bufPt){
  // write this if you need it
	
}

//------------UART1_OutChar------------
// Output 8-bit to serial port
// Do not use interrupts or FIFO, use busy wait
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(char data){
  // write this
	while((UART1_FR_R&0x0020) != 0) {};      // wait until TXFF is 0
  UART1_DR_R = data;
}
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
// RTRIS UART1 receiver has timed out
// Put data into your FIFO
uint32_t Counter = 0;
void UART1_Handler(void){char letter;
  // write this
//0) toggle a heartbeat (change from 0 to 1, or from 1 to 0), 
	PF3 ^= 1;
	while((UART1_FR_R & 0x0010) == 0) {
		letter = (char) (UART1_DR_R & 0xFF); 
	  //letter = UART1_InChar(); 
		Fifo_Put(letter);
		
	}
//1) toggle a heartbeat (change from 0 to 1, or from 1 to 0), 
	PF3 ^= 1; 
//2) as long as the RXFE bit in the UART1_FR_R is zero (should be exactly 8 bytes, but could be more or less)
//   -Read a byte from UART1_DR_R 
//   -Put the byte into your software FIFO 
	Counter++;
//3) Increment a RxCounter, used as debugging monitor of the number of UART messages received
	
//4) acknowledge the interrupt by clearing the flag which requested the interrupt 
  UART1_ICR_R |= 0x40;   // this clears bit 6 (RTRIS) in the RIS register
// 5) toggle a heartbeat (change from 0 to 1, or from 1 to 0),
	PF3 ^= 1; 

}






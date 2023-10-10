// Key.c
// This software configures the off-board piano keys
// Lab 6 requires a minimum of 4 keys, but you could have more
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 1/11/22  
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// **************Key_Init*********************
// Initialize piano key inputs on PA5-2 or PE3-0
// Input: none 
// Output: none
void Key_Init(void){ volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x10; //clock on port E
	for(int i = 0;i<1;i++){}; //waste clock cycle
  GPIO_PORTE_DIR_R &= 0xF0; //PE0-3 are inputs
	GPIO_PORTE_DEN_R |= 0xF;
	
}
// **************Key_In*********************
// Input from piano key inputs on PA5-2 or PE3-0
// Input: none 
// Output: 0 to 15 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2, 0x08 is just Key3
uint32_t Key_In(void){ 
  return GPIO_PORTE_DATA_R&0xF;  
}

//------------LaunchPad_Init------------
// Initialize Switch input and LED output
// Input: none
// Output: none
void LaunchPad_Init(void){
// implement if needed
	SYSCTL_RCGCGPIO_R |= 0x20; //clock on port F
	for(int i = 0;i<1;i++){}; //waste clock cycle
  GPIO_PORTF_DIR_R |= 0x02; //PF1 a output
	GPIO_PORTF_DEN_R |= 0x02;
}


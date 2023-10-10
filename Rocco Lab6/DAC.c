// DAC.c
// This software configures DAC output
// Lab 6 requires 6 bits for the DAC
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 1/11/22 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data



// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
  
	SYSCTL_RCGCGPIO_R |= 0x02; //clock on port B
	for(int i = 0; i < 5; i++); //waste cycles
	GPIO_PORTB_DIR_R |= 0x3F; //PB0-5 are outputs
	GPIO_PORTB_DEN_R |= 0x3F;
  GPIO_PORTB_DR8R_R |= 0x3F; //increase current through DAC

}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Input=n is converted to n*3.3V/63
// Output: none

void DAC_Out(uint8_t data, uint16_t envelope){
		if(GPIO_PORTE_DATA_R != 3){ //if not playing song
			GPIO_PORTB_DATA_R = data;
		}
		else {
			GPIO_PORTB_DATA_R = data/envelope; //accounts for changes in volume throughout the song. envelope is amplitudeDivisor
		}
}

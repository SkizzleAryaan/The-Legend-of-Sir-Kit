// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 1/11/22 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "Music.h"
#include "../inc/tm4c123gh6pm.h"


// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none

const uint8_t wave[64] = { //global wave definition
  32,35,38,41,44,47,49,52,54,56,58,
  59,61,62,62,63,63,63,62,62,61,59,
  58,56,54,52,49,47,44,41,38,35,
  32,29,26,23,20,17,15,12,10,8,
  6,5,3,2,2,1,1,1,2,2,3,
  5,6,8,10,12,15,17,20,23,26,29};

void Sound_Init(void){
	DAC_Init();
	
  //initialize systick
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = 3792;    // reload value, default is key1
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
  NVIC_ST_CTRL_R = 0x07;        // enable SysTick with core clock and interrupts
  
}

// **************Sound_Start*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Start called again, or Sound_Off is called
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Start(uint16_t input){
    NVIC_ST_CTRL_R = 0x07; //enable SysTick
    if(input != 3){
			Music_StopSong();
		}
    else if(input == 3){
			Music_PlaySong();
		}
    //for constant frequencies (non-extra credit code)
    //reloads calculated as 1/(64(freq)(12.5ns))
		if(input == 1){
			NVIC_ST_RELOAD_R = 3792; //reload value, default is key1
		}
		else if(input == 2){
			NVIC_ST_RELOAD_R = 3012; //reload value, default is key1
		}
		else if(input == 4){
			NVIC_ST_RELOAD_R = 2530; //reload value, default is key1
		}
		else if(input == 8){
			NVIC_ST_RELOAD_R = 2256; //reload value, default is key1
		}
}

// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){ 
  NVIC_ST_CTRL_R = 0; //disable SysTick if no input
}

// Interrupt service routine
// Executed every 12.5ns*(period)
uint16_t Count = 0;
void SysTick_Handler(void){
	
	DAC_Out(wave[Count], amplitudeDivisor);
	Count = (Count + 1)&0x3F;
	
}


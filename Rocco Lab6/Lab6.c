// Lab6.c
// Runs on TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// EE319K lab6 starter
// Program written by: Andrew Chang and Rocco Perciavalle
// Date Created: 3/6/17 
// Last Modified: 3/13/22  
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Key.h"
#include "Music.h"
#include "Lab6Grader.h"

// put both EIDs in the next two lines
char EID1[] = "alc6266"; //  ;replace abc123 with your EID
char EID2[] = "rvp425"; //  ;replace abc123 with your EID

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void DAC_Init(void);          // your lab 6 solution
void DAC_Out(uint8_t data);   // your lab 6 solution



int main(void){ 
  DisableInterrupts();
  TExaS_Init(SCOPE);    
  LaunchPad_Init();
  DAC_Init(); // your lab 6 solution
  EnableInterrupts();
	Sound_Init();
	Key_Init();
	Music_Init();
	amplitudeDivisor = 1; //inital value, 1 means playing at max volume
	uint16_t input;
	uint32_t heartBeatCount = 0;
	while(1){
		input = Key_In(); //input is value of button (GPIO data with unneeded bits masked out)
    if(input != 0){ //if there is an input, enable SysTick
      Sound_Start(input);
    }
    else if(input == 0){ 
      Sound_Off();
    }
		if(heartBeatCount == 500000){ //set arbitrary large number so heartbeat isnt annoyingly fast
			GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x02; //XOR LED bit (toggle)
			heartBeatCount = 0;
		}
		heartBeatCount++;
	}
}
	



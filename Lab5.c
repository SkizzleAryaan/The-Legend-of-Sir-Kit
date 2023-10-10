// Lab5.c starter program EE319K Lab 5, Spring 2023
// Runs on TM4C123
// Put your names here

// 2/5/2023 version


/* Option A1, connect LEDs to PB5-PB0, switches to PA5-3, walk LED PF321
   Option A2, connect LEDs to PB5-PB0, switches to PA4-2, walk LED PF321
   Option A6, connect LEDs to PB5-PB0, switches to PE3-1, walk LED PF321
   Option A5, connect LEDs to PB5-PB0, switches to PE2-0, walk LED PF321
   Option B4, connect LEDs to PE5-PE0, switches to PC7-5, walk LED PF321
   Option B3, connect LEDs to PE5-PE0, switches to PC6-4, walk LED PF321
   Option B1, connect LEDs to PE5-PE0, switches to PA5-3, walk LED PF321
   Option B2, connect LEDs to PE5-PE0, switches to PA4-2, walk LED PF321
  */
// east/west red light connected to bit 5
// east/west yellow light connected to bit 4
// east/west green light connected to bit 3
// north/south facing red light connected to bit 2
// north/south facing yellow light connected to bit 1
// north/south facing green light connected to bit 0
// pedestrian detector connected to most significant bit (1=pedestrian present)
// north/south car detector connected to middle bit (1=car present)
// east/west car detector connected to least significant bit (1=car present)
// "walk" light connected to PF3-1 (built-in white LED)
// "don't walk" light connected to PF3-1 (built-in red LED)
#include <stdint.h>
#include "Lab5grader.h"
#include "../inc/tm4c123gh6pm.h"
// put both EIDs in the next two lines
char EID1[] = "abc123"; //  ;replace abc123 with your EID
char EID2[] = "abc123"; //  ;replace abc123 with your EID

void DisableInterrupts(void);
void EnableInterrupts(void);

void Wait10ms(uint32_t time);// implemented in delay.s
int main(void){ 
  DisableInterrupts();
  TExaS_Init(NONE);
  // Initialize GPIO ports
  // Specify initial atate
  EnableInterrupts(); // grader, scope, logic analyzer need interrupts
  while(1){
    // set traffic lights
    // set walk lights
    // wait using Wait10ms
    // read input
    // next state depends on input and current state  
  }
}




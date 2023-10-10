// SysTick.c
// Runs on TM4C123
// Provide functions that initialize the SysTick module, wait at least a
// designated number of clock cycles, and wait approximately a multiple
// of 10 milliseconds using busy wait. 
// Daniel Valvano
// December 31, 2022
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"



// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
    // ECE319K students write this function
  
}
// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void SysTick_Wait(uint32_t delay){
  // ECE319K students write this function
  

}
// 10000us equals 10ms
void SysTick_Wait10ms(uint32_t delay){
    // ECE319K students write this function

}


// TableTrafficLight.c
// Runs on LM4F120/TM4C123
// Use a table implementation of a Moore finite state machine to operate
// a traffic light.
// Daniel Valvano
// February 2, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
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

// north facing car detector connected to PE1 (1=car present)
// east facing car detector connected to PE0 (1=car present)
// east facing red light connected to PB5
// east facing yellow light connected to PB4
// east facing green light connected to PB3
// north facing red light connected to PB2
// north facing yellow light connected to PB1
// north facing green light connected to PB0

#include <stdint.h>
#include "PLL.h"
#include "SysTick.h"
#include "../inc/tm4c123gh6pm.h"


struct State {
  uint32_t Out;      // 6-bit output
  uint32_t Time;     // 10 ms
  uint8_t Next[4];}; // depends on 2-bit input
typedef const struct State State_t;
#define goN   0
#define waitN 1
#define goE   2
#define waitE 3
State_t FSM[4]={
 {0x21,3000,{goN,waitN,goN,waitN}},
 {0x22, 500,{goE,goE,goE,goE}},
 {0x0C,3000,{goE,goE,waitE,waitE}},
 {0x14, 500,{goN,goN,goN,goN}}};

int main(void){
  uint8_t n; // state number
  uint32_t Input;
  PLL_Init(Bus80MHz);               // initialize 80 MHz system clock
  SysTick_Init();                   // initialize SysTick timer
  SYSCTL_RCGCGPIO_R |= 0x12;        // activate clock for Port E and Port B
  // allow time for clock to stabilize
  while((SYSCTL_PRGPIO_R&0x12) != 0x12){};
  GPIO_PORTB_DIR_R |= 0x3F;         // make PB5-0 out
  GPIO_PORTB_DEN_R |= 0x3F;         // enable digital I/O on PB5-0
  GPIO_PORTE_DIR_R &= ~0x03;        // make PE1-0 in
  GPIO_PORTE_DEN_R |= 0x03;         // enable digital I/O on PE1-0
  n = goN;                          // initial state: Green north; Red east
  while(1){ 
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R&~0x3F)|FSM[n].Out;  
    // friendly set lights to current state's Out value
    SysTick_Wait10ms(FSM[n].Time);  // wait 10 ms * current state's Time value
    Input = GPIO_PORTE_DATA_R&0x03; // get new input from car detectors
    n = FSM[n].Next[Input];         // transition to next state
  }
}

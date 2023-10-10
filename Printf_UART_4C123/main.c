// main.c
// Runs on LM4F120/TM4C123
// UART runs at 115,200 baud rate 
// Daniel Valvano
// May 6, 2015

/* This example accompanies the books
  "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
  ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2018

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

#include <stdio.h>
#include <stdint.h> // C99 variable types
#include "../inc/tm4c123gh6pm.h"
void Output_Init(void);
void BookExamples(void){ // examples from the book
  int8_t cc = 0x56; // (‘V’)
  int32_t xx = 100;
  int16_t yy = -100;
  float zz = 3.14159265;
  printf("Hello world\n");	//Hello world
  printf("cc = %c %d %#x\n",cc,cc,cc);	//cc = V 86 0x56
  printf("xx = %c %d %#x\n",xx,xx,xx);	//xx = d 100 0x64
  printf("yy = %d %#x\n",yy,yy);	//yy = -100 0xffffff9c
  printf("zz = %e %E %f %g %3.2f\n",zz,zz,zz,zz,zz);	//zz = 3.14159 3.14
}
int main(void){ int32_t i,n;
  Output_Init();              // initialize output device
  BookExamples();
  n = 0;
  while(1){
    printf("\ni="); 
    for(i=0; i<5; i++){
      printf("%d ",i+n);
    }
    n = n+1000000; // notice what happend when this goes above 2,147,483,647
  }
}
#define LENGTH 100
uint32_t Buf1[LENGTH];
uint32_t Cnt1=0;
void Debug1(void){
  if(Cnt1<LENGTH){
    Buf1[Cnt1++] = GPIO_PORTF_DATA_R;
  }
}
void Debug2(void){
  printf("PortF= 0x%02x\n", GPIO_PORTF_DATA_R);
}
void PortF_Init(void){ volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
  delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}
int main2(void){ 
  uint32_t Start1,Stop1,ExecutionTime1;
  uint32_t Start2,Stop2,ExecutionTime2;
  Output_Init();              // initialize output device
  SysTick_Init();
  PortF_Init();
//*************Profile*****************
  Start1 = NVIC_ST_CURRENT_R;
  Debug1();
  Stop1 = NVIC_ST_CURRENT_R;
  ExecutionTime1 = (Start1-Stop1)&0x0FFFFFF;
  Start2 = NVIC_ST_CURRENT_R;
  Debug2();
  Stop2 = NVIC_ST_CURRENT_R;
  ExecutionTime2 = (Start2-Stop2)&0x0FFFFFF;
  printf("ExecutionTime1= %d cycles\n", ExecutionTime1);
  printf("ExecutionTime2= %d cycles\n", ExecutionTime2);

  while(1){
  }
}

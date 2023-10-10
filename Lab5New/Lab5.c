// Lab5.c starter program EE319K Lab 5, Spring 2023
// Runs on TM4C123
// Put your names here
//Aryaan Saxena and Aastha Agrawal
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
char EID1[] = "as225582"; //  ;replace abc123 with your EID
char EID2[] = "aa92838"; //  ;replace abc123 with your EID

void DisableInterrupts(void);
void EnableInterrupts(void);

void PortE_Init(void) { volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | 0x31; // Turn clock on PortE, A, and F
  delay = 100; // Wait
  GPIO_PORTE_DIR_R = 0x3F; // PF4,PF0 input, PF3-1 output
  GPIO_PORTE_DEN_R = 0x3F; // PF4-PF0 enabled
}

void PortF_Init(void) { volatile uint32_t delay;
  GPIO_PORTF_DIR_R = 0x0E; // PF3-1 output
  GPIO_PORTF_DEN_R = 0x0E; // PF3-PF1 enabled
  GPIO_PORTF_PUR_R = 0x0E; // PF3,PF1 pull up resistor
}

void PortA_Init(void) { volatile uint32_t delay;
  GPIO_PORTA_DIR_R = GPIO_PORTA_DIR_R & 0x00; // PA4-2 input
  GPIO_PORTA_DEN_R = 0x1C; // PA4-PA2 enabled
}

struct State {
  uint32_t LightOut;
	uint32_t WalkOut; 
  uint32_t Time; 
  uint32_t Next[8];
};
typedef const struct State State_t;
#define goN    0
#define waitNE 1
#define goE    2
#define waitEN 3
#define waitEW 4
#define stopN  5
#define waitNW 6
#define RedW   7
#define walk   8
#define warnE  9
#define warnN  10
#define stopE  11
#define RedNE  12
#define RedEN  13
#define Blink1E  14
#define Blink2E  15
#define Blink3E  16
#define Blink1N  17
#define Blink2N  18
#define Blink3N  19
	
State_t FSM[20]={
 {0x21, 0x02, 60000000,{goN,waitNE,goN,waitNE, waitNW, waitNE, waitNW, waitNW}},
 {0x22, 0x02, 10000000,{RedNE,RedNE,RedNE,RedNE, RedNE, RedNE, RedNE, RedNE}},
 {0x0C, 0x02, 60000000,{goE,goE,waitEN,waitEN, waitEW, waitEW, waitEW, waitEN}},
 {0x14, 0x02, 10000000,{RedEN,RedEN,RedEN,RedEN, RedEN, RedEN, RedEN, RedEN}},
 {0x14, 0x02, 10000000,{RedW,RedW,RedW,RedW, RedW, RedW, RedW, RedW}},
 {0x24, 0x02, 6000000,{goN,goN,goN,goN, goN, goN, goN, goN}},
 {0x22, 0x02, 10000000,{RedW,RedW,RedW,RedW, RedW, RedW, RedW, RedW}},
 {0x24, 0x02, 6000000,{walk,walk,walk,walk, walk, walk, walk, walk}},
 {0x24, 0x0E, 20000000,{walk,warnE,warnN,warnN, walk, warnE, warnN, warnE}},
 {0x24, 0x02, 4000000,{Blink1E,Blink1E,Blink1E,Blink1E, Blink1E, Blink1E, Blink1E, Blink1E}},
 {0x24, 0x02, 4000000,{Blink1N,Blink1N,Blink1N,Blink1N, Blink1N, Blink1N, Blink1N, Blink1N}},
 {0x24, 0x02, 6000000,{goE,goE,goE,goE, goE, goE, goE, goE}},
 {0x24, 0x02, 6000000,{goE,goE,goE,goE, goE, goE, goE, goE}},
 {0x24, 0x02, 6000000,{goN,goN,goN,goN, goN, goN, goN, goN}},
 {0x24, 0x00, 4000000,{Blink2E,Blink2E,Blink2E,Blink2E, Blink2E, Blink2E, Blink2E, Blink2E}},
 {0x24, 0x02, 4000000,{Blink3E,Blink3E,Blink3E,Blink3E, Blink3E, Blink3E, Blink3E, Blink3E}},
 {0x24, 0x00, 4000000,{stopE,stopE,stopE,stopE, stopE, stopE, stopE, stopE}},
 {0x24, 0x00, 4000000,{Blink2N,Blink2N,Blink2N,Blink2N, Blink2N, Blink2N, Blink2N, Blink2N}},
 {0x24, 0x02, 4000000,{Blink3N,Blink3N,Blink3N,Blink3N, Blink3N, Blink3N, Blink3N, Blink3N}},
 {0x24, 0x00, 4000000,{stopN,stopN,stopN,stopN, stopN, stopN, stopN, stopN}},
 };
	
	

void Wait10ms(uint32_t time);// implemented in delay.s
 
uint32_t currentState;  // index to the current state
uint32_t Input;
 
int main(void){ 
  DisableInterrupts();
  TExaS_Init(GRADER);
  // Initialize GPIO ports
	PortE_Init();
	PortF_Init();  
	PortA_Init(); 
	
  // Specify initial state
	currentState = goN; 
  EnableInterrupts(); // grader, scope, logic analyzer need interrupts
  while(1){
			// set traffic lights
			//GPIO_PORTE_DATA_R = GPIO_PORTE_DATA_R & 0x00;
			GPIO_PORTE_DATA_R = FSM[currentState].LightOut; 
			// set walk lights
			//GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R & 0x00;
			GPIO_PORTF_DATA_R = FSM[currentState].WalkOut; 
			// wait using Wait10ms
			Wait10ms(FSM[currentState].Time);
		
		// read input
			Input = GPIO_PORTA_DATA_R & 0x1C;
			Input = Input >> 2;
			// next state depends on input and current state 
			currentState = FSM[currentState].Next[Input]; 
     
  }
}



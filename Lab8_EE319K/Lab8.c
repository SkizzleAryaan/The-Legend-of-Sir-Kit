// Lab8.c
// Runs on TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 1/2/2023 

// Specifications:
// Measure distance using slide pot, sample at 10 Hz, using Timer3
// maximum distance can be any value from 1.5 to 2cm
// minimum distance is 0 cm
// Calculate distance in fixed point, 0.001cm
// Analog Input connected to PD2=ADC0 channel 5
// displays distance on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats (use them in creative ways)
// 

#include <stdint.h>

#include "../inc/ST7735.h"
#include "TExaS.h"
#include "../inc/ADC.h"
#include "../inc/tm4c123gh6pm.h"

//*****the first four main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
//       used to test ADC and slide pot
// main2 adds the LCD to the ADC and slide pot, ADC data is on ST7735
//       used to measure execution time of ADC and LCD
// main3 adds your convert function, plot position on ST7735
//       used to test Nyquist Theorem
// main4 used to test Central Limit Theorem
//       observe noise versus ADC0_SAC_R

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
  volatile int delay;
  SYSCTL_RCGCGPIO_R |= 0x20;
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTF_DIR_R |= 0x0E;
  GPIO_PORTF_DEN_R |= 0x0E;
}
uint32_t Data;        // 12-bit ADC
uint32_t Position;    // 32-bit fixed-point 0.001 cm
int main1(void){      // single step this program and look at Data
  DisableInterrupts();
  TExaS_Init(SCOPE);  // Bus clock is 80 MHz 
  ADC_Init();         // turn on ADC, set channel to 5
  EnableInterrupts();
  while(1){                
    Data = ADC_In();  // sample 12-bit channel 5
  }
}
uint32_t startTime,stopTime;
uint32_t ADCtime,Converttime,OutDectime,OutFixtime; // in usec
int main2(void){
  TExaS_Init(SCOPE);  // Bus clock is 80 MHz 
  ADC_Init();         // turn on ADC, set channel to 5
  ST7735_InitR(INITR_REDTAB); 
  NVIC_ST_RELOAD_R = 0x00FFFFFF; // maximum reload value
  NVIC_ST_CURRENT_R = 0;    // any write to current clears it
  NVIC_ST_CTRL_R = 5;
  while(1){           // use scope to measure execution time for ADC_In and ST7735_OutUDec           
    startTime= NVIC_ST_CURRENT_R;
    Data = ADC_In();  // sample 12-bit channel 5
    stopTime = NVIC_ST_CURRENT_R;
    ADCtime = ((startTime-stopTime)&0x0FFFFFF)/80; // usec

    ST7735_SetCursor(0,0);
    startTime= NVIC_ST_CURRENT_R;
    ST7735_OutUDec(Data); 
    ST7735_OutString("    ");  // spaces cover up characters from last output
    stopTime = NVIC_ST_CURRENT_R;
    OutDectime = ((startTime-stopTime)&0x0FFFFFF)/80; // usec
  }
}

// your function to convert 12 bit ADC sample to distance (0.001cm)
// input: x is 12 bit ADC digital sample
// output: integer part of distance in 0.001 resolution
uint32_t Convert(uint32_t x){
  // write this
  return (4405*x)/10000+138;
}
 

int main3(void){ uint32_t time=0;
  volatile uint32_t elapsedTime;
  uint32_t sampleStartTime;
  TExaS_Init(SCOPE);         // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB); 
  NVIC_ST_RELOAD_R = 0x00FFFFFF; // maximum reload value
  NVIC_ST_CURRENT_R = 0;    // any write to current clears it
  NVIC_ST_CTRL_R = 5;
  PortF_Init();
  ADC_Init();         // turn on ADC, set channel to 5
  ST7735_PlotClear(0,2000); 
  while(1){  // fs = 80,000,000/5,000,000 = 16 Hz
    sampleStartTime = NVIC_ST_CURRENT_R;
    PF2 ^= 0x04;      // Heartbeat
    Data = ADC_In();  // sample 12-bit channel 5
    startTime= NVIC_ST_CURRENT_R;
    Position = Convert(Data); 
    stopTime = NVIC_ST_CURRENT_R;
    Converttime = ((startTime-stopTime)&0x0FFFFFF)/80; // usec

    ST7735_SetCursor(0,0);
    ST7735_OutUDec(Data); ST7735_OutString("    "); 
    startTime= NVIC_ST_CURRENT_R;
    ST7735_SetCursor(6,0);
    ST7735_OutFix(Position);
    stopTime = NVIC_ST_CURRENT_R;
    OutFixtime = ((startTime-stopTime)&0x0FFFFFF)/80; // usec
    if((time%8)==0){
      ST7735_PlotPoint(Position);
      ST7735_PlotNextErase(); // data ploted at about 2 Hz
    }
    time++; // executed about every 62.5 ms
    do{
      elapsedTime = (sampleStartTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
    }
    while(elapsedTime <= 5000000);  // establishes approximate sampling rate
  }
} 

uint32_t Histogram[64]; // probability mass function
uint32_t Center;
// main4 program to study CLT
int main4(void){ uint32_t i,d,sac; 
  DisableInterrupts();
  TExaS_Init(SCOPE);    // Bus clock is 80 MHz 
  // Connect PF3 to PD3
  ST7735_InitR(INITR_REDTAB); 
  ADC_Init();        // turn on ADC, PD2, set channel to 5
  PortF_Init();
  EnableInterrupts();
  sac = 0;
  while(1){
    ADC0_SAC_R = sac;
    PF3 ^= 0x08;       // Heartbeat
    Center = ADC_In();
    for(i=0; i<64; i++) Histogram[i] = 0; // clear
    for(i=0; i<200; i++){
      for(int j=0; j<1000 ;j++){};
      Data = ADC_In();
      PF3 ^= 0x08;       // Heartbeat
      if(Data<Center-32){
         Histogram[0]++;
      }else if(Data>=Center+32){
         Histogram[63]++;
      }else{
        d = Data-Center+32;
        Histogram[d]++;
      }
    }
    ST7735_PlotClear(0,100);
    ST7735_SetCursor(0,0);
    ST7735_OutString("SAC = ");
    ST7735_OutUDec(sac);
    for(i=0; i<63; i++){
      if(Histogram[i]>99) Histogram[i]=99;
      ST7735_PlotBar(Histogram[i]);
      ST7735_PlotNext();
      ST7735_PlotBar(Histogram[i]);
      ST7735_PlotNext();
    }
    if(sac<6) sac++;
    else sac = 0;      
  }
}

// ***************** Timer3A_Init ****************
// Activate Timer3 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
//          priority 0 (highest) to 7 (lowest)
// Outputs: none
void Timer3A_Init(uint32_t period, uint32_t priority){
  volatile uint32_t delay;
  SYSCTL_RCGCTIMER_R |= 0x08;   // 0) activate TIMER3
  delay = SYSCTL_RCGCTIMER_R;         // user function
  TIMER3_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER3_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER3_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER3_TAILR_R = period-1;    // 4) reload value
  TIMER3_TAPR_R = 0;            // 5) bus clock resolution
  TIMER3_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER3_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF)|(priority<<29); // priority  
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN1_R = 1<<(35-32);      // 9) enable IRQ 35 in NVIC
  TIMER3_CTL_R = 0x00000001;    // 10) enable timer3A
}

void Timer3A_Stop(void){
  NVIC_DIS1_R = 1<<(35-32);   // 9) disable interrupt 35 in NVIC
  TIMER3_CTL_R = 0x00000000;  // 10) disable timer3
}

uint32_t ADCdata; 
uint32_t ADCflag; 

void Timer3A_Handler(void){
  TIMER3_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
  // write this
	GPIO_PORTF_DATA_R ^= 0x08; // toggle PF1
  ADCdata = ADC_In();      // Sample ADC
  ADCflag = 1;  
}
int main(void){ // this is real lab 8 main
  // write this
	DisableInterrupts();
	PortF_Init();
	TExaS_Init(SCOPE);         // Bus clock is 80 MHz 
	ST7735_InitR(INITR_REDTAB); 
	ADC_Init();  
	Timer3A_Init(8000000, 0);
	EnableInterrupts();

  // 10 Hz sampling in Timer3 ISR
  while(1){
    // check semaphore
    // output to LCD
		if (ADCflag == 1) {
			ST7735_SetCursor(0,0);
			ST7735_OutFix(ADCdata);
			ST7735_OutString("     cm");
			ADCflag = 0; 
	}
  }
}


// SpaceInvaders.c
// Runs on TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the ECE319K Lab 10

// Last Modified: 1/2/2023 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php

// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// buttons connected to PE0-PE3
// 32*R resistor DAC bit 0 on PB0 (least significant bit)
// 16*R resistor DAC bit 1 on PB1
// 8*R resistor DAC bit 2 on PB2 
// 4*R resistor DAC bit 3 on PB3
// 2*R resistor DAC bit 4 on PB4
// 1*R resistor DAC bit 5 on PB5 (most significant bit)
// LED on PD1
// LED on PD0


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "../inc/ADC.h"
#include "Images.h"
#include "../inc/wave.h"
#include "Timer1.h"
#include "Timer0.h"


void Delay10ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240/100;  // 0.1sec at 80 MHz
    while(time){
      time--;
    }
    count--;
  }
}

struct sprite{
	uint8_t x,y;
	uint8_t w,h;
	const uint16_t *image;
};
typedef struct sprite sprite_t;
int8_t dy = 1;
sprite_t sci = {255, 25, 18, 18, o1};
sprite_t sci2 = {255, 25, 18, 18, o2};
sprite_t sci3 = {255, 25, 18, 18, one1};
sprite_t sci4 = {255, 25, 18, 18, one2};
int8_t Timer0_Flag, SciIndex, NumSci, counter = 0;
typedef enum {true,false} boolean_t;

typedef enum {left, right, idle, upatk} walking_t; 
typedef enum {FALSE, TRUE} bool;
 
struct Player{ 
	int16_t x, y; 
	int8_t w, h; 
	bool atk; 
	walking_t motion; 	
	int8_t health;  
};


typedef struct Player player_t; 
int8_t dx = 2; 

int8_t IsOverlap(sprite_t one, player_t p) {
	if((one.x >= (p.x + p.w)) || ((one.x + one.w) <= p.x) || ((one.y - one.h) >= p.y) || (one.y <= (p.y - p.h))) {
		return 0;
	}
	return 1;
}
void Timer0A_Handler(void){ // can be used to perform tasks in background
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
  //sci.y += dy;
	/*
	counter = (counter+1) % 6;
	if(counter == 5) {
		Timer0_Flag = 1;
	}
	*/
	Timer0_Flag = 1;
   //ST7735_DrawBitmap(50, dy, Scissors, 15,16); // execute user task
	
}

void Draw(sprite_t p){
	ST7735_DrawBitmap(p.x, p.y, p.image, p.w, p.h);
};


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds




const uint16_t *Left[2] = {left1, left2};
const uint16_t *Right[2] = {right1, right2};
player_t MainCharacter = {22, 147, 16, 16, FALSE, left, 0}; 
player_t Yerraballi = {50, 45, 42, 42, TRUE, left, 15};  
int8_t anim = 0; 

void MoveLeft(void);
void MoveRight(void);

void PortF_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;      // activate port F
  while((SYSCTL_PRGPIO_R&0x20) != 0x20){};
  GPIO_PORTF_DIR_R |=  0x0E;   // output on PF3,2,1 (built-in LED)
  GPIO_PORTF_PUR_R |= 0x10;
  GPIO_PORTF_DEN_R |=  0x1E;   // enable digital I/O on PF
}

void PortE_Init(void){
	uint32_t delay; 
  SYSCTL_RCGCGPIO_R |= 0x10;      // activate port F
  while((SYSCTL_PRGPIO_R&0x10) != 0x10){};
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTE_DIR_R &=  ~0x03;   // output on PFE,1, 0 (built-in LED)
  //GPIO_PORTE_PUR_R |= 0x10;
  GPIO_PORTE_DEN_R |=  0x03;   // enable digital I/O on PF
}

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
	//MoveLeft(); 
	if (ADCdata <= 1500) 
			 {
				 MoveLeft(); 
			 }
			 else if (ADCdata >= 2500) 
			 {
				 MoveRight(); 
			 }
			 else 
			 {
				 MainCharacter.motion = idle; 
			 }
		//uint32_t atkbut = GPIO_PORTE_DATA_R & 0x02; //pin 1
		/*if (atkbut == 1) 
		{
			MainCharacter.motion = upatk; 
			Attack.x = MainCharacter.x; 
			Attack.y = MainCharacter.y + 8;
			
		}*/
			 
		if (Yerraballi.x > 0 && Yerraballi.motion == left) 
		{
			Yerraballi.x -= dx + 1; 
		}
		else if (Yerraballi.x < 86 && Yerraballi.motion == right)
		{
			Yerraballi.x += dx + 1; 
		}
		
		if (Yerraballi.x <= 0) 
		{
			Yerraballi.motion = right;
		}
		else if (Yerraballi.x >= 86) 
		{
			Yerraballi.motion = left;
		}
	 
}


void Timer1A_Handler(void){ // can be used to perform tasks in background
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
   // execute user task
}








void DrawPlayer(player_t p) {
	if (p.motion == left) 
	{
		ST7735_DrawBitmap(p.x, p.y, Left[anim], p.w, p.h); 
		anim++; 
		if (anim > 1) 
		{
			anim = 0; 
		}
	}
	else if (p.motion == right) 
	{
		ST7735_DrawBitmap(p.x, p.y, Right[anim], p.w, p.h); 
		anim++; 
		if (anim > 1) 
		{
			anim = 0; 
		}
	}
	else if (p.motion == idle) 
	{
		ST7735_DrawBitmap(p.x, p.y, front, p.w, p.h); 
	}
	 
}


//const uint16_t *LeftY[3] = {yleft1, yleft2, yleft3};
//const uint16_t *RightY[3] = {yright1, yright2, yright3};
int8_t yanim = 0; 
void DrawBalli(player_t y) {
	
	if (y.motion == left) 
	{
		ST7735_DrawBitmap(y.x, y.y, yleft1, y.w, y.h); 
		yanim++; 
		if (yanim > 2) 
		{
			yanim = 0; 
		}
	}
	else if (y.motion == right) 
	{
		ST7735_DrawBitmap(y.x, y.y, yright1, y.w, y.h); 
		yanim++; 
		if (yanim > 2) 
		{
			yanim = 0; 
		}
	}
	 
}

void MoveLeft(void) 
{
	if (MainCharacter.x >=0)
	{
		MainCharacter.x -= dx;
	} 
	MainCharacter.motion = left; 
}

void MoveRight(void) 
{
	if (MainCharacter.x <=112)
	{
		MainCharacter.x += dx;
	} 
	MainCharacter.motion = right; 
}

char str1[] = "Score: "; 
char str2[] = "Puntaje: "; 

char str7[] = "VICTORY ACHIEVED";  
char str8[] = "VICTORIA LOGRADA"; 


int main(void){
  DisableInterrupts(); 
  TExaS_Init(NONE);       // Bus clock is 80 MHz 
	ADC_Init(); 
	Timer3A_Init(8000000, 0);
	PortF_Init();
	ST7735_InitR(INITR_REDTAB);
	TExaS_Init(SCOPE);         // Bus clock is 80 MHz 
	PortE_Init(); 
	Timer0_Init(800000000,1); 	
  Random_Init(Random32());
	Wave_Init(); 

  Output_Init();
  ST7735_FillScreen(0xFD06);            // set screen to black
  
  //ST7735_DrawBitmap(22, 159, Aryaan, 16,16); // player ship bottom
	
	EnableInterrupts();

	Timer2A_Start(); 
	uint32_t langcount = 0; 
  while(1)
	{
		DrawPlayer(MainCharacter); 

		DrawBalli(Yerraballi); 
		uint32_t langbut = GPIO_PORTE_DATA_R & 0x01; //pin 0 
		if (langbut == 1) 
		{
			langcount++; 
		}
		if (langcount % 2 == 0)
		{
			
			ST7735_DrawString(0, 15, str1, 0xFD06);
		}
		else 
		{
			ST7735_DrawString(0, 15, str2, 0xFD06);
		} 
		ST7735_FillRect(40, 150, 128, 8, 0x0000);
		ST7735_DrawChar(60, 150, MainCharacter.health + 0x30, 0xFD06, 0x0000, 1);
		//ST7735_SetCursor(50, 100);
		//ST7735_OutUDec(MainCharacter.health);
		//ST7735_SetCursor(50, 100);
		//ST7735_OutUDec(Yerraballi.health);
		
		if (MainCharacter.health >= 10) 
		{
			Timer2A_Start();
			DisableInterrupts(); 
			ST7735_FillScreen(0xFFFF);
			if (langcount % 2 == 0)
			{
				ST7735_DrawString(2, 7, str7, 0xFD06);
			}
			else 
			{
				ST7735_DrawString(2, 7, str8, 0xFD06);
			}
			uint32_t atkbut = GPIO_PORTE_DATA_R & 0x02; //pin 1
			while(atkbut == 0) {
			atkbut = GPIO_PORTE_DATA_R & 0x02;
			}
			MainCharacter.health = 0;
			Yerraballi.health = 25;
			ST7735_FillScreen(0xFD06);  
			EnableInterrupts();
			
			 		
		}
		
		
		if(sci.y < 178) {
			sci.y += dy ;
		}
		if(sci2.y < 178) {
			sci2.y += dy;
		}
		if(sci3.y < 178) {
			sci3.y += dy ;
		}
		if(sci4.y < 178) {
			sci4.y += dy;
		}
		int8_t ak1 = IsOverlap(sci, MainCharacter);
		if (ak1 == 1) 
		{
			
			MainCharacter.health += 1; 
			ST7735_FillRect(sci.x, sci.y - 17, sci.w * 2, sci.h * 2, 0xFD06);
			sci.y = 178; 
				
		}
			
		int8_t ak2 = IsOverlap(sci2, MainCharacter);
		if (ak2 == 1) 
		{
			 
			MainCharacter.health += 1; 
			ST7735_FillRect(sci2.x, sci2.y - 17, sci2.w * 2, sci2.h * 2, 0xFD06);
			sci2.y = 178; 
			
		}
		
		int8_t ak3 = IsOverlap(sci3, MainCharacter);
		if (ak3 == 1) 
		{
			MainCharacter.health += 1;
			ST7735_FillRect(sci3.x, sci3.y - 17, sci3.w * 2, sci3.h * 2, 0xFD06);
			sci3.y = 178; 
			 
		}
		
		int8_t ak4 = IsOverlap(sci4, MainCharacter);
		if (ak4 == 1) 
		{ 
			MainCharacter.health += 1; 
			ST7735_FillRect(sci4.x, sci4.y - 17, sci4.w * 2, sci4.h * 2, 0xFD06);
			sci4.y = 178; 
			
		}	
		Delay10ms(1);
		Draw(sci);
		Draw(sci2);
		Draw(sci3);
		Draw(sci4);
		if ((Timer0_Flag == 1)) {
			NumSci = (Random()%4)+1;
				if(NumSci == 1) {
					sci.y = 0;
					sci.x = Random()%112;
				}
				if(NumSci == 2) {
					sci.y = 0;
					sci2.y = 0;
					sci.x = Random()%48;
					sci2.x = Random()%(112-(sci.x+sci.w))+(sci.x+sci.w);
				}
				if(NumSci == 3) {
					sci.y = 0;
					sci2.y = 0;
					sci3.y = 0;
					sci.x = Random()%21;
					sci2.x = Random()%(112-(sci.x+sci.w))+(sci.x+sci.w);
					if(sci2.x <= 94){
						sci3.x = Random()%(112-(sci2.x+sci2.w))+(sci2.x+sci2.w);
					} else {
						sci3.x = 255;
					}
				}
				if(NumSci == 4) {
					sci.y = 0;
					sci2.y = 0;
					sci3.y = 0;
					sci4.y = 0;
					sci.x = Random()%12;
					sci2.x = Random()%(112-(sci.x+sci.w))+(sci.x+sci.w);
					if(sci2.x <= 94){
						sci3.x = Random()%(112-(sci2.x+sci2.w))+(sci2.x+sci2.w);
					} else {
						sci3.x = 255;
					}
					if(sci3.x <= 94) {
						sci4.x = Random()%(112-(sci3.x+sci3.w))+(sci3.x+sci3.w);
					} else {
						sci4.x = 255;
					}
				}
			Timer0_Flag = 0;
		}
		
			
		
		
		
 }

}





// You can't use this timer, it is here for starter code only 
// you must use interrupts to perform delays
void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
      time--;
    }
    count--;
  }
}
typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};

int main1(void){ char l;
  DisableInterrupts();
  TExaS_Init(NONE);       // Bus clock is 80 MHz 
  Output_Init();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<= French; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Delay100ms(30);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Delay100ms(20);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }  
}


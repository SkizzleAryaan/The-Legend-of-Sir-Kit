// Music.c
// playing your favorite song.
//
// For use with the TM4C123
// EE319K lab6 extra credit
// Program written by: put your names here
// 1/11/22

#include "Sound.h"
#include "DAC.h"
#include "Music.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value

/*
calculated timer delays before interrupting to get correct frequency for each note. 
calculated as 1/((64)(freqency of note)(12.5ns)) where 64 is the number of steps in the sine wave.
*/
#define A 2841
#define Bflat 2681
#define C 4778
#define D 4257
#define E 3792
#define F 3579
#define G 3189

uint16_t SongCount = 0; //iterator through song.
  
struct Song{
  uint16_t note;
  uint16_t length; //stores realtive length of notes, quarter notes are 2x as long as 8th notes
  uint16_t envelope; //stores values that will be used to divide amplitude of wave so volume can vary over time.
};

typedef const struct Song Song_t;
Song_t Christmas[32]={ //struct stores 'We Wish You a Merry Christmas' as collection of notes, lengths, and "envelope values" (volume)
  {C,2,32},
  {F,2,32},
  {F,1,32},
  {G,1,32},
  {F,1,32},
  {E,1,32},
  {D,2,32},
  {D,2,32},
  {D,2,16},
  {G,2,16},
  {G,1,16},
  {A,1,16},
  {G,1,16},
  {F,1,16},
  {E,2,16},
  {C,2,16},
  {C,2,4},
  {A,2,4},
  {A,1,4},
  {Bflat,1,4},
  {A,1,4},
  {G,1,4},
  {F,2,4},
  {D,2,4},
  {C,1,1},
  {C,1,1},
  {D,2,1},
  {G,2,1},
  {E,2,1},
  {F,2,1},
  {F,1,1},
  {F,1,1}
};

uint8_t amplitudeDivisor = 1; //inital value, divisor divides volume.
void Music_Init(void){
	//reset song
	SongCount = 0;
	//enable TIMER0A
	long sr;
	sr = StartCritical(); //cannot be interrupted until EndCritical
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = 20000000;    // 4) reload value, default to quarter note length at 120bpm (0.5 sec), first note in song.
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // 8) priority 2
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
  EndCritical(sr);
}

// Play song, while button pushed or until end
uint8_t inputHeld = 0;
void Music_PlaySong(void){
 
  inputHeld = 1;
	
}

// Stop song
void Music_StopSong(void){
  
	inputHeld = 0;
	Music_Init(); //reset music when stopped.
	
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT; //acknowledge timer0A timeout
	if(inputHeld){
	NVIC_ST_RELOAD_R = Christmas[SongCount].note; //retrieve data about song from struct
	TIMER0_TAILR_R = 20000000*Christmas[SongCount].length; //calculate and set reload value for interrupt to next note
	amplitudeDivisor = Christmas[SongCount].envelope;
	SongCount = (SongCount + 1)&0x1F;
	}
}

// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 1/17/2020 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "../inc/tm4c123gh6pm.h"
#include "../PeriodicSysTickInts_4C123/SysTickInts.c"
// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
uint8_t Index=0;
uint32_t Period =  2500000/523;//Set to a c note;
uint32_t flag = 0;
// 4-bit 32-element sine wave
const unsigned short wave[32] = {
  8,9,11,12,13,14,14,15,15,15,14,
  14,13,12,11,9,8,7,5,4,3,2,
  2,1,1,1,2,2,3,4,5,7};

void Sound_Init(void){
  DAC_Init();          // Port B is DAC
  SysTick_Init(0);
	EnableInterrupts();
}

void SysTick_Handler(void){
	if(flag == 1){
	Index = (Index+1)&0x1F;   
  DAC_Out(wave[Index]);    // output one value each interrupt
	}
}

// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period){
	if(period == 0){
		flag = 0; 
	}
	else{
		flag = 1;
	}
	
	NVIC_ST_RELOAD_R = period;
	
}


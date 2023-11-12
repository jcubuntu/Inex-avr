//------------------------------------------------------------------------------------------------//
// Program	: Library for gennerate sound   
// Description 	: Library for generate easy sound
// Frequency	: Crystal 12 MHz at PLL 5x(CCLK = 60 MHz),PCLK = 30 MHz 
// Filename	: sound.h
// C compiler	: Keil CARM Compiler
//------------------------------------------------------------------------------------------------//
#ifndef _SOUND_H_
#define _SOUND_H_
#include "pins_arduino.h"
#include "wiring_private.h"

void __delay_sound(uint16_t ms) // private
{
	unsigned int i;
	for(i=0;i<ms;i++)
	delayMicroseconds(10);
}

void sound(uint8_t pin,uint16_t freq,uint32_t time)
{
	uint32_t dt=0,m=0;	// Keep value and 
	uint32_t tempTime;
    	pinMode(pin,OUTPUT);
	digitalWrite(pin,LOW);
    	tempTime=time*50;
    	dt = 50000/freq;   	// Keep active logic delay
	time = (tempTime)/dt;	// Keep counter for generate sound
	for(m=0;m<time;m++) // Loop for generate sound(Toggle logic P0.12)   
	{
	  digitalWrite(pin,HIGH);
	  __delay_sound(dt);
	  digitalWrite(pin,LOW);
	  __delay_sound(dt);
	}		
}

void beep(uint8_t pin)
{
	sound(pin,500,100);
}
#endif




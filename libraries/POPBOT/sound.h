//------------------------------------------------------------------------------------------------//
// Program	: Library for gennerate sound   
// Description 	: Library for gennerate easy sound at PWM3 pin
// Frequency	: Crytal 16 MHz  
// Filename	: sound.h
// C compiler	: Wirring
//------------------------------------------------------------------------------------------------//
#ifndef _SOUND_H_
#define _SOUND_H_
#include "pins_arduino.h"
#include "wiring_private.h"
#define RBX168_SOUND_PIN 14
void delay_sound(uint16_t ms) // private
{
	unsigned int i;
	for(i=0;i<ms;i++)
    delayMicroseconds(10);
}

void sound(uint16_t freq,uint32_t time)
{
	uint32_t dt=0,m=0;	// Keep value and 
	uint32_t tempTime;
	digitalWrite(RBX168_SOUND_PIN,LOW);
    pinMode(RBX168_SOUND_PIN,OUTPUT);
    tempTime=time*50;
    dt = 50000/freq;   	// Keep active logic delay
	time = (tempTime)/dt;	// Keep counter for generate sound
	for(m=0;m<time;m++) // Loop for generate sound(Toggle logic P0.12)   
	{
	  digitalWrite(RBX168_SOUND_PIN,HIGH);
	  delay_sound(dt);
	  digitalWrite(RBX168_SOUND_PIN,LOW);
	  delay_sound(dt);
	}		
}

#endif




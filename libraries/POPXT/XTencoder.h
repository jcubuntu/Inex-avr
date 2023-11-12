//------------------------------------------------------------------------------------------------//
// Encoder INT 0 1 2 3
// Update:	resetEnc(channel)
//			readEnc(channel)
//			encoder(channel,preloadValue)
//------------------------------------------------------------------------------------------------//
#ifndef _POPXT_ENCODER_H_
#define _POPXT_ENCODER_H_

#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define pinEncoder3 3
#define pinEncoder2 2
#define pinEncoder0 0
#define pinEncoder1 1
volatile unsigned int encCnt0,encCnt1,encCnt2,encCnt3;

volatile bool __attachedINT0=false;
volatile bool __attachedINT1=false;
volatile bool __attachedINT2=false;
volatile bool __attachedINT3=false;

void enc0Changed()
{ encCnt0++; }

void resetEnc0()
{ encCnt0=0; }

unsigned int readEnc0()
{ return encCnt0; }

void enc1Changed()
{ encCnt1++; }

void resetEnc1()
{ encCnt1=0; }

unsigned int readEnc1()
{ return encCnt1; }

void enc2Changed()
{ encCnt2++; }

void resetEnc2()
{ encCnt2=0; }

unsigned int readEnc2()
{ return encCnt2; }

void enc3Changed()
{ encCnt3++; }

void resetEnc3()
{ encCnt3=0; }

unsigned int readEnc3()
{ return encCnt3; }

unsigned int encoder(int channel)
{
	switch(channel)
	{
	  case 3: if (!__attachedINT0)
		{
	    __attachedINT0=true;
		// encoder INT0
		encCnt3=0; // Clear slot counter
		pinMode(pinEncoder3,INPUT_PULLUP);
		attachInterrupt(0, enc3Changed, CHANGE);
		// end encoder
		}
		return encCnt3;
		break;
	  case 2: if (!__attachedINT1)
	    {
	    __attachedINT1=true;
		// encoder INT1
		encCnt2=0; // Clear slot counter
		pinMode(pinEncoder2,INPUT_PULLUP);
		attachInterrupt(1, enc2Changed, CHANGE);
		// end encoder
		}
		return encCnt2;
		break;
	  case 0: if (!__attachedINT2)
	    {
		__attachedINT2=true;
		// encoder INT2
		encCnt0=0; // Clear slot counter
		pinMode(pinEncoder0,INPUT_PULLUP);
		attachInterrupt(2, enc0Changed, CHANGE);
		// end encoder
		}
		return encCnt0;
		break;
	  case 1: if (!__attachedINT3)
		{
	    __attachedINT3=true;
		// encoder INT3
		encCnt1=0; // Clear slot counter
		pinMode(pinEncoder1,INPUT_PULLUP);
		attachInterrupt(3, enc1Changed, CHANGE);
		// end encoder
		}
		return encCnt1;
		break;
	  default:
		return 0;
	}
}

void encoder(int channel,int preloadValue)
{
	switch(channel)
	{
	  case 3: if (!__attachedINT0)
		{
	    __attachedINT0=true;
		// encoder INT0
		pinMode(pinEncoder3,INPUT_PULLUP);
		attachInterrupt(0, enc3Changed, CHANGE);
		// end encoder
		}
		encCnt3=preloadValue; // Clear slot counter
		break;
	  case 2: if (!__attachedINT1)
	    {
	    __attachedINT1=true;
		// encoder INT1
		pinMode(pinEncoder2,INPUT_PULLUP);
		attachInterrupt(1, enc2Changed, CHANGE);
		// end encoder
		}
		encCnt2=preloadValue; // Clear slot counter
		break;
	  case 0: if (!__attachedINT2)
	    {
		__attachedINT2=true;
		// encoder INT2
		pinMode(pinEncoder0,INPUT_PULLUP);
		attachInterrupt(2, enc0Changed, CHANGE);
		// end encoder
		}
		encCnt0=preloadValue; // Clear slot counter
		break;
	  case 1: if (!__attachedINT3)
		{
	    __attachedINT3=true;
		// encoder INT3
		pinMode(pinEncoder1,INPUT_PULLUP);
		attachInterrupt(3, enc1Changed, CHANGE);
		// end encoder
		}
		encCnt1=preloadValue; // Clear slot counter
		break;
	}
}

void resetEnc(int channel)
{
	switch(channel)
	{
	  case 0: encCnt0=0; break;
	  case 1: encCnt1=0; break;
	  case 2: encCnt2=0; break;
	  case 3: encCnt3=0; break;
	}
}

unsigned int readEnc(int channel)
{
	switch(channel)
	{
	  case 0: return encCnt0;
	  case 1: return encCnt1;
	  case 2: return encCnt2;
	  case 3: return encCnt3;
	}
}


#endif
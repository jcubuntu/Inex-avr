//------------------------------------------------------------------------------------------------//
// Encoder INT2
//------------------------------------------------------------------------------------------------//
#ifndef _ATX2_ENC_H_
#define _ATX2_ENC_H_

#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define pinEncoder 18
#define pinEncoder18 18
#define pinEncoder2 2
#define pinEncoder3 3

volatile unsigned int encCnt,encCnt2,encCnt3,encCnt18;

volatile bool __attachedINT0=false;
volatile bool __attachedINT1=false;
volatile bool __attachedINT2=false;

void encChanged()
{ encCnt++;  encCnt18++; }

void resetEnc()
{ encCnt=0; encCnt18=0; }

unsigned int readEnc()
{ return encCnt; }

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

void enc18Changed()
{ encCnt18++; }

void resetEnc18()
{ encCnt18=0; }

unsigned int readEnc18()
{ return encCnt18; }

void encoder_reset(int channel)
{
	switch(channel)
	{
	  case 2: encCnt2=0; break;
	  case 3: encCnt3=0; break;
	  case 18: encCnt18=0; break;
	  case 0: encCnt=0; break;
	}
}

void resetEnc(int channel)
{
	switch(channel)
	{
	  case 2: encCnt2=0; break;
	  case 3: encCnt3=0; break;
	  case 18: encCnt18=0; break;
	  case 0: encCnt=0; break;
	}
}

unsigned int readEnc(int channel)
{
	switch(channel)
	{
	  case 2: return encCnt2;
	  case 3: return encCnt3;
	  case 18: return encCnt18;
	  case 0: return encCnt;
	}
}

unsigned int encoder(int channel)
{
	switch(channel)
	{
	  case 2: if (!__attachedINT0)
		{
	    __attachedINT0=true;
		// encoder INT0
		encCnt2=0; // Clear slot counter
		pinMode(pinEncoder2,INPUT_PULLUP);
		attachInterrupt(0, enc2Changed, CHANGE);
		// end encoder
		}
		return encCnt2;
		break;
	  case 3: if (!__attachedINT1)
	    {
	    __attachedINT1=true;
		// encoder INT1
		encCnt3=0; // Clear slot counter
		pinMode(pinEncoder3,INPUT_PULLUP);
		attachInterrupt(1, enc3Changed, CHANGE);
		// end encoder
		}
		return encCnt3;
		break;
	  case 18: if (!__attachedINT2)
	    {
		__attachedINT2=true;
		// encoder INT2
		encCnt18=0; // Clear slot counter
		pinMode(pinEncoder18,INPUT_PULLUP);
		attachInterrupt(2, enc18Changed, CHANGE);
		// end encoder
		}
		return encCnt18;
		break;
	  default:
		return 0;
	}
}


unsigned int encoder()
{
  if (!__attachedINT2)
  {
	__attachedINT2=true;
	// encoder INT2
	encCnt=0; // Clear slot counter
	encCnt18=0; // Clear slot counter
	pinMode(pinEncoder18,INPUT_PULLUP);
	attachInterrupt(2, encChanged, CHANGE);
	// end encoder
  }
   return encCnt;
}

void encoder(int channel,int preloadValue)
{
	switch(channel)
	{
	  case 2: if (!__attachedINT0)
		{
	    __attachedINT0=true;
		// encoder INT0
		pinMode(pinEncoder2,INPUT_PULLUP);
		attachInterrupt(0, enc2Changed, CHANGE);
		// end encoder
		}
		encCnt2=preloadValue; // Clear slot counter
		break;
	  case 3: if (!__attachedINT1)
	    {
	    __attachedINT1=true;
		// encoder INT1
		pinMode(pinEncoder3,INPUT_PULLUP);
		attachInterrupt(1, enc3Changed, CHANGE);
		// end encoder
		}
		encCnt3=preloadValue; // Clear slot counter
		break;
	  case 18: if (!__attachedINT2)
	    {
		__attachedINT2=true;
		// encoder INT2
		pinMode(pinEncoder18,INPUT_PULLUP);
		attachInterrupt(2, enc18Changed, CHANGE);
		// end encoder
		}
		encCnt18=preloadValue; // Clear slot counter
		break;
	}
}

#endif
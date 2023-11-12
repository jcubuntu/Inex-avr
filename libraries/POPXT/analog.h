#ifndef _ANALOG_H_
#define _ANALOG_H_
#include "pins_arduino.h"
#include "wiring_private.h"
//#define knob() analog(8)

int __knobLastValue=0;

unsigned int analog(char ch)
{
 analogRead(ch);
 return(analogRead(ch));         
}
unsigned char sw_ok()
{
 
 if(analogRead(8)<10)
 {
   return(1);
 }
 return(0);
}
void sw_ok_press()
{
 while(analogRead(8)>10);
 while(analogRead(8)<=10);     
}
unsigned char sw_OK()
{
 
 if(analog(8)<10)
 {
   return(1);
 }
 return(0);
}
void sw_OK_press()
{
 while(analog(8)>10);
 while(analog(8)<=10);     
}

unsigned int knob(void)
{
  int __knobValue;
  analogRead(8);
  __knobValue=analogRead(8);
  if (__knobValue>64)
  {
	__knobLastValue=__knobValue;
  }
  return(__knobLastValue);
}

unsigned int knob(unsigned int scale)
{
  unsigned int value;
//  analogRead(7);
//  value=analogRead(7);
  value=knob();
  if (value<123)
  {
	value=123;
  }
  value-=123;
  // unit in 900 count
  value=value/(900/scale);
  if (value>scale)
  {
	value=scale;
  }
  return(value);
}

int knob(int scaleCCW,int scaleCW)
{
  int value;
//  analogRead(7);
//  value=analogRead(7);
  value=knob();
  if (value<123)
  {
	value=123;
  }
  value-=123;
  // unit in 900 count
  
  if (scaleCW>=scaleCCW)
  {
	value=value/(900/(scaleCW-scaleCCW));
	value+=scaleCCW;
	if (value>scaleCW)
	{
	  value=scaleCW;
	}
  }
  else
  {
	value=900-value;
	value=value/(900/(scaleCCW-scaleCW));
	value+=scaleCW;
	if (value>scaleCCW)
	{
	  value=scaleCCW;
	}
  }
  return(value);
}



#endif

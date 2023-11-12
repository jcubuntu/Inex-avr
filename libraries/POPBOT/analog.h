#ifndef _ANALOG_H_
#define _ANALOG_H_
#include "pins_arduino.h"
#include "wiring_private.h"
#define knob() analog(7)
unsigned int analog(char ch)
{
 analogRead(ch);
 return(analogRead(ch));         
}

unsigned int sensor(char ch)
{
 analogRead(ch);
 return(analogRead(ch));         
}

#endif

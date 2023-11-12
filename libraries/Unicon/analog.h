#ifndef _ANALOG_H_
#define _ANALOG_H_
#include "pins_arduino.h"
#include "wiring_private.h"
#define knob() analog(8)
unsigned int analog(char ch)
{
 analogRead(ch);
 return(analogRead(ch));         
}
unsigned char sw_ok()
{
 
 if(knob()<10)
 {
   return(1);
 }
 return(0);
}
void sw_ok_press()
{
 while(knob()>10);
 while(knob()<=10);     
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

#endif

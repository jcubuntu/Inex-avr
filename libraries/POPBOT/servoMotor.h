#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_
#include <Sm.h>
#include <Sm.h>
//#include <WProgram.h>
#include "pins_arduino.h"
#include "wiring_private.h"

Sm __servo[2];
void servo(char ch,unsigned int pos)
{
     if(ch==7 || ch==8)
     {
      __servo[ch-7].attach(ch);
      __servo[ch-7].write(pos);
     }
}
int servo_read(char ch)
{
     if(ch==7 || ch==8)
     {
      return(__servo[ch-7].read());
     }
     return(-1);
}
int servo_get_status(char ch)
{
     if(ch==7 || ch==8)
     {
      return(__servo[ch-7].attached());
     }
     return(-1);
}
void servo_stop(char ch)
{
     if(ch==7 || ch==8)
     {
       if(servo_get_status(ch)==1)
       {__servo[ch-7].detach();}
     }
     else if(ch==ALL)
     {
       for(int i=7;i<=8;i++)
       {
          if(servo_get_status(i)==1)
          {__servo[i-7].detach();}               
       }
     }
}



#endif


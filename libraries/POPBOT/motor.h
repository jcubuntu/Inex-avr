#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "pins_arduino.h"
#include "wiring_private.h"

#define MOTOR_A 1
#define MOTOR_B 2

#ifndef ALL 
#define ALL 100
#endif

#define ao() motor_stop(ALL)
//#define off(x) motor_stop(x) // remark for avoid .off function conflict
void motor(char ch,int pow)
{
     int p=0;
     //long p=0;
     pinMode(3,OUTPUT);
     pinMode(5,OUTPUT);
     pinMode(6,OUTPUT);
     pinMode(9,OUTPUT);
     if(pow>=-100 && pow<=100)
     {
         p = (pow*255)/100;   // 8 bit resolution
         if(ch==1 && pow>=0)
         {
              analogWrite(3,p);
              digitalWrite(5,LOW);
         }
         else if(ch==1 && pow<0)
         {
              analogWrite(5,-p);
              digitalWrite(3,LOW);
         }
         else if(ch==2 && pow>=0)
         {
              analogWrite(6,p);
              digitalWrite(9,LOW);
         }
         else if(ch==2 && pow<0)
         {
              analogWrite(9,-p);
              digitalWrite(6,LOW);
         }
      }
}
void motor_stop(char ch)
{
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    if(ch==1)
    {  
       digitalWrite(3,LOW);
       digitalWrite(5,LOW); 
    }
    else if(ch==2)
    {  
       digitalWrite(6,LOW);
       digitalWrite(9,LOW); 
    }   
    else if(ch==ALL)
    {
       digitalWrite(3,LOW);
       digitalWrite(5,LOW); 
       digitalWrite(6,LOW);
       digitalWrite(9,LOW);
    }
}
void fd(int speed)
{
     motor(1,speed);
     motor(2,speed);
}
void bk(int speed)
{
     motor(1,-speed);
     motor(2,-speed);
}
void tl(int speed)
{
     motor(1,0);
     motor(2,speed);
}
void tr(int speed)
{
     motor(1,speed);
     motor(2,0);
}
void sl(int speed)
{
     motor(1,-speed);
     motor(2,speed);
}
void sr(int speed)
{
     motor(1,speed);
     motor(2,-speed);
}

#endif

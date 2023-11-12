#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "pins_arduino.h"
#include "wiring_private.h"

#ifndef ALL
 #define ALL 100
#endif
#ifndef all
 #define all 100
#endif
#define __POPXT_mtrAdir 5
#define __POPXT_mtrApwm 9
#define __POPXT_mtrBdir 7
#define __POPXT_mtrBpwm 10
#define ao() motor_stop(ALL)

volatile int __motorLastSpeed=0;

void motor(uint8_t mtr,int8_t speed)
{
  signed int speedMotor;
  pinMode(__POPXT_mtrAdir,OUTPUT);
  pinMode(__POPXT_mtrBdir,OUTPUT);
  
  if(speed>=-100 && speed<=100)
  {
      __motorLastSpeed=speed;
      speedMotor=(speed*255)/100;

	  if (mtr==1)
	  {
		if (speed>0)
		{
		  digitalWrite(__POPXT_mtrAdir,LOW);
		}
		else
		{
		  digitalWrite(__POPXT_mtrAdir,HIGH);
		}
		analogWrite(__POPXT_mtrApwm,abs(speedMotor));
	  }
	  if (mtr==2)
	  {
		if (speed>0)
		{
		  digitalWrite(__POPXT_mtrBdir,LOW);
		}
		else
		{
		  digitalWrite(__POPXT_mtrBdir,HIGH);
		}
		analogWrite(__POPXT_mtrBpwm,abs(speedMotor));
	  }
	  if ((mtr==ALL)||(mtr==12))
	  {
		if (speed>0)
		{
		  digitalWrite(__POPXT_mtrAdir,LOW);
		  digitalWrite(__POPXT_mtrBdir,LOW);
		}
		else
		{
		  digitalWrite(__POPXT_mtrAdir,HIGH);
		  digitalWrite(__POPXT_mtrBdir,HIGH);
		}
		analogWrite(__POPXT_mtrApwm,abs(speedMotor));
		analogWrite(__POPXT_mtrBpwm,abs(speedMotor));
		}
	  }
}

void motor_stop(uint8_t ch)
{
    pinMode(__POPXT_mtrAdir,OUTPUT);
    pinMode(__POPXT_mtrBdir,OUTPUT);
    if(ch==1)
    {  
	  motor(1,0);
    }
    else if(ch==2)
    {  
	  motor(2,0);
    }   
    else if((ch==ALL)||(ch==12))
    {
	  motor(ALL,0);
    }
	__motorLastSpeed=0;
}

void motor(char ch,int speed,int step)
{
	int i;
	if (speed>__motorLastSpeed)
	{
	  for (i=__motorLastSpeed;i<=speed;i++)
	  {
		motor(ch,i);
		delay(step);
	  }
	  __motorLastSpeed=speed;
	}
	else
	{
	  for (i=__motorLastSpeed;i>=speed;i--)
	  {
		motor(ch,i);
		delay(step);
	  }
	  __motorLastSpeed=speed;
	}
}

void fd(int8_t speed)
{
     motor(1,speed);
     motor(2,speed);
}
void fd2(int8_t speed1,int8_t speed2)
{
	 motor(1,speed1);
     motor(2,speed2);
} 
void bk(int8_t speed)
{
     motor(1,-speed);
     motor(2,-speed);
}
void bk2(int8_t speed1,int8_t speed2)
{
	 motor(1,-speed1);
     motor(2,-speed2);
}
void tl(int8_t speed)
{
     motor(1,0);
     motor(2,speed);
}
void tr(int8_t speed)
{
     motor(1,speed);
     motor(2,0);
}
void sl(int8_t speed)
{
     motor(1,-speed);
     motor(2,speed);
}
void sr(int8_t speed)
{
     motor(1,speed);
     motor(2,-speed);
}

void fd(int8_t speed,int step)
{
     motor(1,speed);
     motor(2,speed);
}
void bk(int8_t speed,int step)
{
     motor(1,-speed);
     motor(2,-speed);
}
void tl(int8_t speed,int step)
{
     motor(1,0);
     motor(2,speed);
}
void tr(int8_t speed,int step)
{
     motor(1,speed);
     motor(2,0);
}
void sl(int8_t speed,int step)
{
     motor(1,-speed);
     motor(2,speed);
}
void sr(int8_t speed,int step)
{
     motor(1,speed);
     motor(2,-speed);
}
#endif

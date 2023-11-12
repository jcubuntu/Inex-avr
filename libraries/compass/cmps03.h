//------------------------------------------------------------------------------------//
// Program		: Library for i2c bus   
// Description 	: Library for i2c bus(TWI)
// Frequency	: Crystal 16 MHz 
// Filename		: i2c.h
// C compiler	: WinAVR
//------------------------------------------------------------------------------------//
#ifndef _IPST_CMPS03_LIB_H_
#define _IPST_CMPS03_LIB_H_

#define CMPS03_ADDR 0xC0
#include <avr/io.h>	// Header file for AVR MCU 
//#include "ipst_i2c.h"	// Include Library for TW interface	
#include <./../compass/compass_i2c.h>

char __cmps03_ini=0,__cmps03_heading_ini=0;
char __cmps03_ini2=0,__cmps03_heading_ini2=0;
int __cmps03_heading=0;
int __cmps03_heading2=0;
int __cmps03_pwm_pin = 17;
//----------------------------------------------------------------------------//
//---------------------- Function i2c start condition  -----------------------//
//----------------------------------------------------------------------------//
void cmps03_init()
{
  if(__cmps03_ini==0)
  {
    __cmps03_ini=1;
	TWBR = 60;	// Ensure decrease bit rate i2c bus                    
  }     
}
void cmps03_init2()
{
  if(__cmps03_ini2==0)
  {
    __cmps03_ini2=1;
	TWBR = 60;	// Ensure decrease bit rate i2c bus                    
  }     
}
int cmps03_read()
{
	unsigned int dat;
	cmps03_init();
    i2c_start();		// Start condition
    i2c_write(CMPS03_ADDR);	// Send MCP23016 ID 
    i2c_write(2);	// Send MCP23016 ID 
    i2c_stop();	
    delay(1);	// calibrate (old value 10 ms) 
    i2c_start();	// Restart condition
    i2c_write(CMPS03_ADDR+1);	// Send CMPS03 ID for Read mode	
    dat = i2c_read(ACK);	// Read high byte from CMPS03(wait acknowledge)
    dat <<=8;				// Shift bit for high byte
    dat |= i2c_read(NACK); // Read low byte from CMPS03(none acknowledge)
    i2c_stop();					// Stop condition
    return(dat/10);		// Return value div 10
  
}
int cmps03_pwm_read(int pin)
{
	long angle;
	pinMode(pin,INPUT);
	cmps03_init2();
	long duration = pulseIn(pin,HIGH);
	angle = duration/100-10;
    return(angle);		// Return value div 10
}

void cmps03_set_heading()
{
  __heading = cmps03_read();
  if(__cmps03_heading_ini==0)
  {
    __cmps03_heading_ini= 1;                     
  }
}
void cmps03_pwm_set_heading(int __pin)
{
  __cmps03_pwm_pin = __pin;
  __heading = cmps03_pwm_read(__pin);
  if(__cmps03_heading_ini2==0)
  {
    __cmps03_heading_ini2= 1;                     
  }
}

int cmps03_read_heading()
{
  int ang_new=0,a=0,offset,dir_pos,dir_neg,dif;
  a = cmps03_read();
  // Positive direction
  dir_pos = __heading+180;
  //dir_neg = __heading+180;
  if(__heading>=180 && __heading<=359)
  {
    if(dir_pos<359)
    {
      ang_new = a-__heading;                                
    }
    else
    {
      if(a>=0 && a<=(dir_pos-360))
      {
        ang_new = (360-__heading)+a;
      }
      else
      {
        ang_new = a-__heading;
        //lcd("#n %d   ",a);
      }         
    }
  }
  else
  {
    ang_new = a-__heading;
    if(a>=0 && a<=__heading)
    {
      ang_new = a-__heading;
    }
    else if(a>=(__heading+180) && a<=359)
    {
      ang_new = (-1)*(__heading+(360-a)); 
    }
  }

  return(ang_new);
}

int cmps03_pwm_read_heading()
{
  int ang_new=0,a=0,offset,dir_pos,dir_neg,dif;
  a = cmps03_pwm_read(__cmps03_pwm_pin);
  // Positive direction
  dir_pos = __heading+180;
  //dir_neg = __heading+180;
  if(__heading>=180 && __heading<=359)
  {
    if(dir_pos<359)
    {
      ang_new = a-__heading;                                
    }
    else
    {
      if(a>=0 && a<=(dir_pos-360))
      {
        ang_new = (360-__heading)+a;
      }
      else
      {
        ang_new = a-__heading;
        //lcd("#n %d   ",a);
      }         
    }
  }
  else
  {
    ang_new = a-__heading;
    if(a>=0 && a<=__heading)
    {
      ang_new = a-__heading;
    }
    else if(a>=(__heading+180) && a<=359)
    {
      ang_new = (-1)*(__heading+(360-a)); 
    }
  }

  return(ang_new);
}


#endif
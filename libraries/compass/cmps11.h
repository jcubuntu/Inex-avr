//------------------------------------------------------------------------------------//
// Program		: Library for i2c bus   
// Description 	: Library for i2c bus(TWI)
// Frequency	: Crystal 16 MHz 
// Filename		: i2c.h
// C compiler	: WinAVR
//------------------------------------------------------------------------------------//
#ifndef _CMPS11_LIB_H_
#define _CMPS11_LIB_H_

#define CMPS11_ADDR 0xC0
#ifndef MODE_SERIAL
#define MODE_SERIAL 1
#endif
#ifndef MODE_I2C
#define MODE_I2C 2
#endif

#include <avr/io.h>	// Header file for AVR MCU 
//#include "ipst_i2c.h"	// Include Library for TW interface	
#include <./../compass/compass_i2c.h>
#include <./../INEX/inex_serial.h> // M16/32 OK

char __cmps11_connect_mode = MODE_I2C,__cmps11_ini=0,__cmps11_heading_ini=0;
char __cmps11_ini2=0,__cmps11_heading_ini2=0;
int __cmps11_heading=0;
int __cmps11_heading2=0;

void cmps11_i2c_init()
{
  if(__cmps11_ini==0)
  {
    __cmps11_ini=1;
	TWBR = 60;	// Ensure decrease bit rate i2c bus                    
  }     
}
void cmps11_mode(char mode)
{
	__cmps11_connect_mode = mode;
}

int cmps11_read()
{
	unsigned char H,L;
	unsigned int angle;
	if(__cmps11_connect_mode==MODE_SERIAL)
	{
		uart1_putc(0x13);     // CMPS11 get angle     
		while(uart1_available() < 2);
		H = uart1_getkey();
		L = uart1_getkey();
		angle=((H<<8)+L)/10;
	}
	else if(__cmps11_connect_mode==MODE_I2C)
	{
		cmps11_i2c_init();
		i2c_start();		// Start condition
		i2c_write(CMPS11_ADDR);	// Send MCP23016 ID 
		i2c_write(2);	// Send MCP23016 ID 
		i2c_stop();	
		delay(1);	// calibrate (old value 10 ms) 
		i2c_start();	// Restart condition
		i2c_write(CMPS11_ADDR+1);	// Send CMPS11 ID for Read mode	
		angle = i2c_read(ACK);	// Read high byte from CMPS11(wait acknowledge)
		angle <<=8;				// Shift bit for high byte
		angle |= i2c_read(NACK); // Read low byte from CMPS11(none acknowledge)
		i2c_stop();					// Stop condition
		angle = angle/10;
	}
	return(angle);
	
}
void cmps11_set_heading()
{
  __heading = cmps11_read();
  if(__cmps11_heading_ini==0)
  {
    __cmps11_heading_ini= 1;                     
  }
}
int cmps11_read_heading()
{
  int ang_new=0,a=0,offset,dir_pos,dir_neg,dif;
  a = cmps11_read();
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
int cmps11_read_pitch()	// Pitch +/- 85
{
	int pitch;
	if(__cmps11_connect_mode==MODE_SERIAL)
	{
		uart1_putc(0x14);     // CMPS11 get pitch     
		while(uart1_available() < 1);
		pitch = uart1_getkey();
	}
	else if(__cmps11_connect_mode==MODE_I2C)
	{
		cmps11_i2c_init();
		i2c_start();		// Start condition
		i2c_write(CMPS11_ADDR);	// Send MCP23016 ID 
		i2c_write(4);	// Send MCP23016 ID 
		i2c_stop();	
		delay(1);	// calibrate (old value 10 ms) 
		i2c_start();	// Restart condition
		i2c_write(CMPS11_ADDR+1);	// Send CMPS11 ID for Read mode	
		pitch |= i2c_read(NACK); // Read low byte from CMPS11(none acknowledge)
		i2c_stop();					// Stop condition
	}
	if(pitch>90)	// down angle
	{
		pitch  = pitch-255;	// negative side for down angle
	}
	return(pitch);
} 
int cmps11_read_roll()
{
	int roll;
	if(__cmps11_connect_mode==MODE_SERIAL)
	{
		uart1_putc(0x15);     // CMPS11 get pitch     
		while(uart1_available() < 1);
		roll = uart1_getkey();
	}
	else if(__cmps11_connect_mode==MODE_I2C)
	{
		cmps11_i2c_init();
		i2c_start();		// Start condition
		i2c_write(CMPS11_ADDR);	// Send MCP23016 ID 
		i2c_write(5);	// Send MCP23016 ID 
		i2c_stop();	
		delay(1);	// calibrate (old value 10 ms) 
		i2c_start();	// Restart condition
		i2c_write(CMPS11_ADDR+1);	// Send CMPS11 ID for Read mode	
		roll |= i2c_read(NACK); // Read low byte from CMPS11(none acknowledge)
		i2c_stop();					// Stop condition
	}
	if(roll>90)	// down angle
	{
		roll  = roll-255;	// negative side for down angle
	}
	return(roll);
} 
/*int cmps11_read_temp()
{
	unsigned char H,L;
	unsigned int temp;
	uart1_putc(0x22);     // CMPS11 get angle     
	while(uart1_available() < 2);
	H = uart1_getkey();
	L = uart1_getkey();
	//temp=(H<<8)+L;
	temp=L;
	return(temp);
} 
*/


#endif
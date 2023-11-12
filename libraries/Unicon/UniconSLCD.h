/*
  Encoder.cpp - Encoder library for Wiring & Arduino
  Copyright (c) 2006 Hernando Barragan and Nicholas Zambetti.
  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _UNICONSLCD_H_
#define _UNICONSLCD_H_
//#include <WProgram.h>
#include "pins_arduino.h"
#include "wiring_private.h"

#include <stdlib.h>
#include <ctype.h>

#define slcd_clear() slcd_command(1)
#define slcd_origin() slcd_command(2)
#define slcd lcd
#define printf lcd

//-------------------- Condition  test parameter data type for display ---------------//
#ifndef TEST_CHAR_TYPE(x)
#define TEST_CHAR_TYPE(x) *x=='%' && (*(x+1)=='c' || *(x+1)=='C')
#endif

#ifndef TEST_BIN_TYPE(x)
#define TEST_BIN_TYPE(x) *x=='%' && (*(x+1)=='b' || *(x+1)=='B')
#endif

#ifndef TEST_HEX_TYPE(x)
#define TEST_HEX_TYPE(x) *x=='%' && (*(x+1)=='h' || *(x+1)=='H')
#endif

#ifndef TEST_INT_TYPE(x)
#define TEST_INT_TYPE(x) *x=='%' && (*(x+1)=='d' || *(x+1)=='D')
#endif

#ifndef TEST_LONG_TYPE(x)
#define TEST_LONG_TYPE(x) *x=='%' && (*(x+1)=='l' || *(x+1)=='L')
#endif

#ifndef TEST_FLOAT_TYPE(x)
#define TEST_FLOAT_TYPE(x) *x=='%' && (*(x+1)=='f' || *(x+1)=='F')
#endif

#ifndef TEST_CLEAR_NEXT_TYPE(x)
#define TEST_CLEAR_NEXT_TYPE(x) *x== '#' && *(x+1)=='c' // Clear display next time
#endif

#ifndef TEST_NEW_LINE_TYPE(x)
#define TEST_NEW_LINE_TYPE(x) *x== '#' && *(x+1)=='n' 	// Go to line 2
#endif


#ifndef SET_FLOAT_PREC
#define SET_FLOAT_PREC 1
unsigned int _floatPrecision=3;
void setFloatPrecision(unsigned int prec)
{
	_floatPrecision=prec;
}
#endif

//------------------------------------------------------------------------------------//
void slcd_config(void);
void slcdConfig(uint8_t,uint16_t);

//void slcd_init(void);
char slcd_ini=0,slcd_clear_display=0;
unsigned char slcdPin=1;       // Default SCLD pin    
unsigned char slcdBaud=0;

void slcd_wr_byte(unsigned char outbyte)
{
  unsigned int bauddelay;

//  uint8_t oldSREG = SREG;
//  cli();  // turn off interrupts for a clean txmit

  if (slcdBaud==1)
  {//2400
	bauddelay=411; //Range 388-435.. from fine tuned.. replace 416
  }
  else
  {//9600
	bauddelay=96; // Range 91-101.. from fine tuned.. replace 104
  }
  delayMicroseconds(bauddelay);
  digitalWrite(slcdPin,LOW);
  delayMicroseconds(bauddelay);
  
  for (byte mask = 0x01; mask; mask <<= 1)
  {
	if (outbyte & mask) // choose bit
	  digitalWrite(slcdPin,HIGH);
    else
	  digitalWrite(slcdPin,LOW);    

	delayMicroseconds(bauddelay);
  }
  
  digitalWrite(slcdPin,HIGH);
  delayMicroseconds(bauddelay);
  delayMicroseconds(bauddelay);
//  SREG = oldSREG; // turn interrupts back on

}

void slcd_command(unsigned char outbyte)	/* Send command */
{
  if(slcd_ini==0)
  {
  	slcd_ini=1;
	slcd_config();
  }
  slcd_wr_byte(0xFE);
  delay(1);
  slcd_wr_byte(outbyte);
  delay(1);
}

//void lcd_text(unsigned char outbyte)
void slcd_text(char outbyte) /* Send Data */
{
  if(slcd_ini==0)
  {
  	slcd_ini=1;
	slcd_config();
  }
  slcd_wr_byte(outbyte);
  delay(1);
}
//-----------------------------------------------------------------------------------------------------------------------------//
//------------------------------------ Function show string message ----------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------//
void slcd_puts(unsigned char line,char *p)
{
	slcd_origin();         // Set origin address of LCD
	slcd_command(line);			// Set address 00H of LCD
	while(*p)                  // Check data pointer = 0?
	{
	 slcd_text(*p);             // Send data to LCD
	 p++;                      // Increase address 1 time 
	}
}
//-----------------------------------------------------------------------------------------------------------------------------//
//------------------------- Convert integer to ascii for display on LCD ---------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------//
/*void inttolcd(unsigned char posi, long value)
{
	char buff[16];			// For keep string send to LCD 
	ltoa(value,&buff[0],10);
	slcd_puts(posi,buff);  	// Send integer to LCD
}*/
void slcdPort(uint8_t Pin)
{
//  slcdPin(__txPin);
  slcdPin=Pin;
  digitalWrite(slcdPin,HIGH);
  delay(500);
  pinMode(slcdPin,OUTPUT);
  //slcd.begin(9600);
  //slcd.begin(slcd_baud);
  delay(100);
  slcd_clear();      // Ensure clear screen at first time
}

void slcd_config(void)
{
//  slcdPin(__txPin);
  digitalWrite(slcdPin,HIGH);
  delay(500);
  pinMode(slcdPin,OUTPUT);
  //slcd.begin(9600);
  //slcd.begin(slcd_baud);
  delay(100);
  slcd_clear();      // Ensure clear screen at first time
}

void slcdConfig(uint8_t Pin,uint16_t baud)
{
  slcdPin=Pin;
  digitalWrite(slcdPin,HIGH);
  delay(500);
  pinMode(slcdPin,OUTPUT);
  if (baud==2400)
  {
	slcdBaud=1;
   }
  else
  {
	slcdBaud=0;
  }
  delay(100);
  slcd_clear();      // Ensure clear screen at first time
}
//-----------------------------------------------------------------------------------------------------------------------------//
//------------------------------------ Function LCD display and %d support(Beta version) ----------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------//
void slcd(char *p,...)
{
	char *arg,**pp;	// Poter of point
	char *ptr,char_count=0,buff[16];
	pp = &p;
	ptr = p;	// Copy address
	arg = (char *)pp;	// Copy address of p point
	
	slcd_origin();       // Set origin address of LCD
	slcd_command(0x80);	// Set address 00H of LCD
	if(slcd_clear_display)
	{
		slcd_clear_display = 0;
		slcd_clear();
	}
	arg += 2;	// Cross 2 time go to Origin of first parameter 
	
	while(*ptr)                 // Check data pointer = 0?
	{
	 	if(TEST_CHAR_TYPE(ptr))
		{
			char_count++;
			if(char_count==17)
			{
				slcd_origin();
				slcd_command(0xC0);
			}
			if(char_count>32)
			{
				char_count = 0;
			}
			slcd_text(toascii(*arg));             // Send data to LCD
	 	
			arg+=2;	// Cross address char type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_BIN_TYPE(ptr))
		{
			p = ultoa(*(unsigned int *)arg,&buff[0],2);
			while(*p)           // Check data pointer = 0?
			{
	 			char_count++;
				if(char_count==17)
				{
					slcd_origin();
					slcd_command(0xC0);
				}
				if(char_count>32)
				{
					char_count = 0;
				}
				slcd_text(*p);             // Send data to LCD
	 			p++;                     // Increase address 1 time 
			}
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_HEX_TYPE(ptr))
		{
			p = ultoa(*(unsigned int *)arg,&buff[0],16);
			while(*p)           // Check data pointer = 0?
			{
	 			char_count++;
				if(char_count==17)
				{
					slcd_origin();
					slcd_command(0xC0);
				}
				if(char_count>32)
				{
					char_count = 0;
				}
				slcd_text(*p);             // Send data to LCD
	 			p++;                     // Increase address 1 time 
			}
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_INT_TYPE(ptr))
		{
			p = ltoa(*(int *)arg,&buff[0],10);
			while(*p)           // Check data pointer = 0?
			{
	 			char_count++;
				if(char_count==17)
				{
					slcd_origin();
					slcd_command(0xC0);
				}
				if(char_count>32)
				{
					char_count = 0;
				}
				slcd_text(*p);             // Send data to LCD
	 			p++;                     // Increase address 1 time 
			}
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_LONG_TYPE(ptr))
		{
			p = ltoa(*(long *)arg,&buff[0],10);
			while(*p)           // Check data pointer = 0?
			{
	 			char_count++;
				if(char_count==17)
				{
					slcd_origin();
					slcd_command(0xC0);
				}
				if(char_count>32)
				{
					char_count = 0;
				}
				slcd_text(*p);             // Send data to LCD
	 			p++;                     // Increase address 1 time 
			}
			arg+=4;	// Cross address long type
			ptr++;	// Cross %l parameter
		}
		else if(TEST_FLOAT_TYPE(ptr))
		{
			p = dtostrf(*(float *)arg,2,_floatPrecision,&buff[0]);	// Convert float to string(used libm.a)
			while(*p)           // Check data pointer = 0?
			{
	 			char_count++;
				if(char_count==17)
				{
					slcd_origin();
					slcd_command(0xC0);
				}
				if(char_count>32)
				{
					char_count = 0;
				}
				slcd_text(*p);             // Send data to LCD
	 			p++;                     // Increase address 1 time 
			}
			arg+=4;	// Cross address long type
			ptr++;	// Cross %l parameter
		}
		else if(TEST_CLEAR_NEXT_TYPE(ptr))
		{
			slcd_clear_display = 1;	// Clear display next time 
			
			ptr++;	// Cross %l parameter
		}
		else if(TEST_NEW_LINE_TYPE(ptr))
		{
			
			char_count = 17;	// Character start line 2 
			slcd_origin();
			slcd_command(0xC0);		
			ptr++;	// Cross %l parameter
		}
		else
		{
			char_count++;
			if(char_count==17)
			{
				slcd_origin();
				slcd_command(0xC0);
			}
			if(char_count>32)
			{
				char_count = 0;
			}
			slcd_text(*ptr);             // Send data to LCD
	 	}
		
		ptr++;                      // Increase address 1 time 
	}

}
#endif




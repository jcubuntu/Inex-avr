//------------------------------------------------------------------------------------------------//
// Program	: LED8 Library Write serial data 9600bps to digital I/O   
// Description 	: LED8 Library Write serial data 9600bps to digital I/O   
// Frequency	: Crytal 16 MHz  
// Filename	: ipst_led8.h
// C compiler	: Wiring
//------------------------------------------------------------------------------------------------//
#ifndef _INEX_LED8_H_
#define _INEX_LED8_H_

#include <avr/io.h>
#include <util/delay.h>
#define _baud9600_bitdelay 0.10

#define _baud9600_microsDelay 102

void pinLED8(int);
void LED8(unsigned char);
void LED8(int,unsigned char);

unsigned int _pinLED8Assigned=0;
int _pinLED8Port;

void pinLED8(int num)
{
  _pinLED8Assigned=1;
  _pinLED8Port=num;
}

void LED8(unsigned char _dat)
{
  if (_pinLED8Assigned!=0)
  {
    LED8(_pinLED8Port,_dat);
  }
  else
  {
    # warning "led8pin not assigned, no output!"
  }
}

void LED8(int _pinLED8Port,unsigned char _dat)
{
	unsigned long startMicros;
	startMicros=micros();
	
	digitalWrite(_pinLED8Port,HIGH);
	pinMode(_pinLED8Port, OUTPUT);
	while(micros()<(startMicros+_baud9600_microsDelay));

	digitalWrite(_pinLED8Port,LOW);
	while(micros()<(startMicros+(2*_baud9600_microsDelay)));

	if ((_dat&0x01)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(3*_baud9600_microsDelay)));

	if ((_dat&0x02)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(4*_baud9600_microsDelay)));

	if ((_dat&0x04)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(5*_baud9600_microsDelay)));

	if ((_dat&0x08)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(6*_baud9600_microsDelay)));

	if ((_dat&0x10)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(7*_baud9600_microsDelay)));

	if ((_dat&0x20)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(8*_baud9600_microsDelay)));

	if ((_dat&0x40)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(9*_baud9600_microsDelay)));

	if ((_dat&0x80)!=0) { digitalWrite(_pinLED8Port,HIGH); }
	else { digitalWrite(_pinLED8Port,LOW); }
	while(micros()<(startMicros+(10*_baud9600_microsDelay)));

	digitalWrite(_pinLED8Port,HIGH);
	while(micros()<(startMicros+(11*_baud9600_microsDelay)));

#if defined(ARDUINO) && (ARDUINO >= 103)
	pinMode(_pinLED8Port, INPUT_PULLUP);
#else
	pinMode(_pinLED8Port, INPUT);
#endif

}

#endif
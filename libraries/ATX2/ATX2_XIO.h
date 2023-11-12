//------------------------------------------------------------------------------------------------//
// Library XIO Co-processor
//------------------------------------------------------------------------------------------------//
#ifndef _ATX2_XIO_H_
#define _ATX2_XIO_H_
#include <ATX2_in_out.h>
#include <ATX2_sleep.h>
#include <ATX2_SPI.h>
#include <ATX2_glcd.h>
#include <ATX2_enc.h> // Encoder on pin 18 (INT2)

#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
//#include <WApplet.c>
#endif

#define	enableXIO_CS	PORTC&=0xEF
#define	disableXIO_CS	PORTC|=0x10

extern byte __XIO_cmdResponse;
extern byte __XIO_dataByte0Response;
extern byte __XIO_dataByte1Response;
//extern byte __XIO_dataByte2Response;
extern unsigned int __XIO_dataWordResponse;
char _xio_ini = 0;

void XIOinit();
void __XIOxfer(byte cmdByte,byte dataByte0,byte dataByte1,byte dataByte2)
{
/*    disableXIO_CS;
	if(_xio_ini==0)
	{
		XIOinit(); // init SPI for GLCD and XIO
		_xio_ini=1;
        delayMicroseconds(600);
	}
*/
      ATX2_SPI.setClockDivider(SPI_CLOCK_DIV32);
      ATX2_SPI.setDataMode(SPI_MODE3);
      enableXIO_CS;
      //delay(2);
      ATX2_SPI.transfer(cmdByte);
      delay(2);
      __XIO_cmdResponse=ATX2_SPI.transfer(dataByte0);
      delayMicroseconds(200);
      __XIO_dataByte0Response=ATX2_SPI.transfer(dataByte1);
      delayMicroseconds(200);
      __XIO_dataByte1Response=ATX2_SPI.transfer(dataByte2);
      delayMicroseconds(200);
      disableXIO_CS;
      delayMicroseconds(600);
}

void XIOreset()
{
// Clear piezo
// Clear A8-A12
// Clear LB LED
// Clear motor
// Clear servo
  __XIOxfer(0xff,0xff,0xff,0xff); delayMicroseconds(2000);
  __XIOxfer(0x00,0xff,0xff,0xff); delayMicroseconds(2000);
  __XIOxfer(0x9f,0xff,0xff,0xff); delayMicroseconds(2000);
}

void XIOinit()
{
  // pre-define UART0,UART1 weak pull-up
  pinMode(0,INPUT_PULLUP);
  pinMode(1,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);

  pinMode(22,INPUT_PULLUP);

  digitalWrite(12,HIGH);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  glcdClear(); delayMicroseconds(2000);
  XIOreset(); delayMicroseconds(2000);
//  __XIOxfer(0x9f,0xff,0xff,0xff); delayMicroseconds(2000); //deteched all servos
//  __XIOxfer(0x13,0x00,0xff,0xff); delayMicroseconds(2000); //deteched all motors
}

void XIO()
{
  // pre-define UART0,UART1 weak pull-up
  pinMode(0,INPUT_PULLUP);
  pinMode(1,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);

  pinMode(22,INPUT_PULLUP);

  digitalWrite(12,HIGH);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  glcdClear(); delayMicroseconds(2000);
  XIOreset(); delayMicroseconds(2000);
//  __XIOxfer(0x9f,0xff,0xff,0xff); delayMicroseconds(2000); //deteched all servos
//  __XIOxfer(0x13,0x00,0xff,0xff); delayMicroseconds(2000); //deteched all motors
}

// removed due to XIO replacement
//void sound(uint8_t pin,uint16_t freq,uint32_t time)
//{
//
//}

#endif

//#ifndef _ATX2_TPA_H_
//#define _ATX2_TPA_H_
#ifndef _ATX2_H_
#define _ATX2_H_

#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
//#include <WApplet.c>
#endif

#include <ATX2_XIO.h> //
#include <ATX2_motor.h>	 // M16/32 OK
#include <ATX2_sleep.h>  //
#include <ATX2_sound.h>  //
#include <ATX2_in_out.h> //

#include <ATX2_sonar.h> //
//#include <ATX2_gp2d120.h> //

#include <ATX2_analog.h> // M16/32 OK

#include <ATX2_glcd.h>
//#include <ATX2_serial.h> // M16/32 OK
#include <./../INEX/inex_serial.h> // M16/32 OK
#include <ATX2_servoMotor.h>
#include <./../INEX/inex_led8.h> //

#include <ATX2_enc.h> //
//#include <ATX2_compass.h> //

#include <./../compass/compass.h>

byte __XIO_cmdResponse;
byte __XIO_dataByte0Response;
byte __XIO_dataByte1Response;
unsigned int __XIO_dataWordResponse;
 
void OK(void)
{
  int state=0;
  // servo
  /*PORTC&=0x1F;
  DDRC|=0xE0;*/
  // End servo
//  delay(100);
  XIOinit(); // init SPI for GLCD and XIO
  __XIOxfer(0x00,0xff,0xff,0xff); delayMicroseconds(2000);
  __XIOxfer(0x9f,0xff,0xff,0xff); delayMicroseconds(2000);
  glcdMode(1);
  setTextSize(3);
  setTextColor(GLCD_ORANGE);
  glcd(1,2,"A");
  setTextColor(GLCD_YELLOW);
  glcd(1,3,"T");
  setTextColor(GLCD_WHITE);
  glcd(1,4,"X");
   setTextColor(GLCD_VIOLET);
  glcd(1,5,"-");
  setTextColor(GLCD_PINK);
  glcd(1,6,"2");
  setTextSize(2);
  setTextColor(GLCD_DARKGRAY);
  glcd(6,2,"---   ---");
  setTextColor(GLCD_GRAY);
  glcd(6,5,"---");
  setTextColor(GLCD_DOLLAR);
  glcd(5,3,"Push   ");
  setTextColor(GLCD_SKY);
  while(sw_OK()==0)
  {
    if (state==0)
    {
      glcd(5,8,"OK");
    }
    else
    {
      glcd(5,8,"  ");
    }
  delay(150);
  state=state^0x01;
  }
  setTextColor(GLCD_WHITE);
  glcdClear();
}


#endif

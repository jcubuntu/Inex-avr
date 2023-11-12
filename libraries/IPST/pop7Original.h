#ifndef _POPX2_H_
#define _POPX2_H_
#define _POP7_H_

#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ipst_motor.h>	 // M16/32 OK
#include <ipst_sleep.h>  //
#include <ipst_in_out.h> //

// integrated sonar
#include <ipst_sonar.h> //
#include <ipst_enc.h> //
#include <ipst_analog.h> // M16/32 OK

#include <ipst_glcd.h>
#include <ipst_sound.h> //

void OK(void)
{
  int state=0;
  int n;
  delay(500);
  glcdSetColorWordBGR();
  glcdClear();
  setTextColor(GLCD_WHITE);
  glcdMode(0);

  __tft.drawChar(10,24,'P', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(30,24,'O', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(50,24,'P', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(70,24,'-', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(88,18,'7', GLCD_LIME ,GLCD_BLACK,5);

  setTextSize(1);
  setTextColor(GLCD_ORANGE);
  glcd(5,2,"controller");

  setTextSize(2);
  setTextColor(GLCD_MAGENTA);
  glcd(4,2,"C");
  setTextColor(GLCD_BLUE);
  glcd(4,3,"O");
  setTextColor(GLCD_GREEN);
  glcd(4,4,"L");
  setTextColor(GLCD_YELLOW);
  glcd(4,5,"O");
  setTextColor(0xfe00);
  glcd(4,6,"R");
  setTextColor(GLCD_RED);
  glcd(4,7,"!");

  beep(12); delay(100); beep(12);

  pinMode(22,INPUT);
  digitalWrite(22,HIGH);

  setTextColor(GLCD_WHITE);
  glcd(6,2,"Push ");

  setTextColor(GLCD_GREEN);
  while(!sw_OK())
  {
    glcd(6,7,"OK");
    for (n=0;n<25;n++)
    {
      delay(10);
      if (sw_OK())
      {
        break;
      }
    }
    glcd(6,7,"  ");
    for (n=0;n<25;n++)
    {
      delay(10);
      if (sw_OK())
      {
        break;
      }
    }
  }
  sound(12,800,100);
  glcdClear();
  setTextSize(1);
  setTextColor(GLCD_WHITE);
  glcdMode(0);
}

//#include <ipst_serial.h> // M16/32 OK
#include <./../INEX/inex_serial.h> // M16/32 OK
#include <ipst_servoMotor.h>

#include <./../INEX/inex_led8.h> //
#include <./../INEX/gp2d120.h> // GP2D Distance sensor
#include <./../compass/compass.h> // Compass HMC5983/5883/6352
#include <./../compass/cmps03.h> // CMPS03
#include <./../compass/cmps11.h> // CMPS11

#endif

#ifndef _POPX2_TPA_H_
#define _POPX2_TPA_H_
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
  int n;
  delay(500);
  glcdSetColorWordBGR();
  glcdClear();
  setTextColor(GLCD_WHITE);
  glcdMode(0);
//  setTextSize(3);
//  setTextColor(GLCD_SKY);
//  glcd(1,0,"POP-");
//  setTextColor(GLCD_LIME);
//  setTextSize(6);
//  glcd(0,2,"7");
  __tft.drawChar(10,24,'P', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(30,24,'O', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(50,24,'P', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(70,24,'-', GLCD_SKY ,GLCD_BLACK,3);
  __tft.drawChar(88,18,'7', GLCD_LIME ,GLCD_BLACK,5);

  setTextSize(1);
  setTextColor(GLCD_ORANGE);
  glcd(5,2,"controller");

  setTextSize(2);
  setTextColor(GLCD_SKY);
  glcd(4,1,"T");
  glcd(4,2,"P");
  glcd(4,3,"A");
  __tft.drawChar(54,82,'2', GLCD_YELLOW ,GLCD_BLACK,3);
  __tft.drawChar(70,82,'0', GLCD_YELLOW ,GLCD_BLACK,3);
  __tft.drawChar(86,82,'1', GLCD_YELLOW ,GLCD_BLACK,3);
  __tft.drawChar(102,82,'9', GLCD_YELLOW ,GLCD_BLACK,3);
  setTextSize(1);
  setTextColor(GLCD_WHITE);
  glcd(10,2,"JUNIOR");
  setTextSize(2);

  beep(12); delay(100); beep(12);

  pinMode(22,INPUT);
  digitalWrite(22,HIGH);

  int i,j,r,g,b;
  i=0;
  for (j=5;j<=120;j++)
  {
      r=(45-i)-(j/4)-1;
      g=(((50-i)-(j/4))<<1)-1;
      b=(55)-(j/4)-1;
      glcdLine(j,i+120,j,i+124,(r<<11)|(g<<5)|b);
  }

  setTextColor(GLCD_WHITE);
  glcd(7,2,"Push ");

  setTextColor(GLCD_GREEN);
  while(!sw_OK())
  {
    glcd(7,7,"OK");
    for (n=0;n<25;n++)
    {
      delay(10);
      if (sw_OK())
      {
        break;
      }
    }
    glcd(7,7,"  ");
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

#ifndef _POPX2_H_
#define _POPX2_H_

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
  setTextSize(3);
  setTextColor(GLCD_SKY);
  glcd(1,1,"POP");
  setTextColor(GLCD_ORANGE);
  setTextSize(6);
  glcd(1,1,"X2");

  setTextSize(2);
  setTextColor(GLCD_WHITE);
  glcd(7,2,"Push ");

  setTextColor(GLCD_BLUE);
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

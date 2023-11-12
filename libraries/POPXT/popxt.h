#ifndef _POPXT_H_
#define _POPXT_H_
#include "in_out.h"
#include "sleep.h"
#include "analog.h"
#include "glcd.h"
#include "sound.h"
#include "motor.h"
#include "XT_servoMotor.h"
#include <./../INEX/inex_serial.h>
#include <./../INEX/gp2d120.h>
#include "XTencoder.h"

void OK(void)
{
  int state=0;
  delay(100);
  glcdMode(1);
  setTextSize(3);
  setTextColor(GLCD_BLUE);
  glcd(1,1,"POP");
  setTextColor(GLCD_DARKGREEN);
  glcd(1,4,"-");
  setTextColor(GLCD_ORANGE);
  glcd(1,5,"XT");
  setTextColor(GLCD_DOLLAR);
  glcd(1,7,"+");
  setTextSize(2);
  setTextColor(GLCD_DARKGRAY);
  glcd(4,2,"---   ---");
  setTextColor(GLCD_GRAY);
  glcd(4,5,"---");
  setTextColor(GLCD_DARKGRAY);
  glcd(6,2,"---   ---");
  setTextColor(GLCD_GRAY);
  glcd(6,5,"---");
  setTextColor(GLCD_PINK);
  glcd(5,3,"Push   ");
  setTextColor(GLCD_YELLOW);
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
  setTextColor(GLCD_GREEN);
  glcd(5,1,"> Running..");
  delay(250);
  setTextColor(GLCD_WHITE);

}

#endif

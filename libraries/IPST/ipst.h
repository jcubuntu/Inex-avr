#ifndef _IPST_H_
#define _IPST_H_
//#ifndef _IPST_TPA_H_
//#define _IPST_TPA_H_

#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
//#include <WApplet.c>
#endif

#include <ipst_motor.h>	 // M16/32 OK
#include <ipst_sleep.h>  //
#include <ipst_in_out.h> //

// integrated sonar
#include <ipst_sonar.h> //
#include <ipst_enc.h> //
#include <ipst_analog.h> // M16/32 OK

#if defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) 
  #include <ipst_lcd.h> // character LCD for IPST 16/32
#else
  #include <ipst_glcd.h>
  void OK(void)
  {
    int state=0;
    glcdClear(); glcdMode(1);setTextSize(2);
    setTextColor(GLCD_WHITE);
    glcd(4,1,"> Push   ");
    setTextColor(GLCD_YELLOW);
    while(sw_OK()==0)
    { 
      if (state==0)
      {
        glcd(4,8,"OK");
      }
      else
      {
        glcd(4,8,"  ");
      }
	  delay(150);
	  state=state^0x01;
    }
    setTextColor(GLCD_GREEN);
    glcd(4,1,"> Running..");
    delay(250);
    setTextColor(GLCD_WHITE);
  }
#endif

#include <ipst_sound.h> //
#include <./../INEX/inex_serial.h> // M16/32 OK
#include <ipst_servoMotor.h>

// DSP4S
#include <./../DSP4S/dsp4s.h> // on Standard kit #3

#include <./../INEX/mcp9701.h> //
#include <./../INEX/gp2d120.h> //
#include <./../INEX/inex_led8.h> //
#include <./../compass/compass.h> // Compass HMC5983/5883/6352
#include <./../compass/cmps03.h> // CMPS03
#include <./../compass/cmps11.h> // CMPS11

#endif

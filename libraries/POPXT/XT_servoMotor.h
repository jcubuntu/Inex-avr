#ifndef _XT_SERVOMOTOR_H_
#define _XT_SERVOMOTOR_H_

#include "Servo.h"
// flags for function set
#define __POPXT_servo1 30
#define __POPXT_servo2 12
#define __POPXT_servo3 13
Servo popXTservo1;
Servo popXTservo2;
Servo popXTservo3;
#ifndef ALL
 #define ALL 100
#endif

void servo(uint8_t servo,int16_t angle)
{
  if (servo==ALL)
  {
    if (angle==-1)
	{
	  popXTservo1.detach();
	  popXTservo2.detach();
	  popXTservo3.detach();
	}
	else
	{
      if (!(popXTservo1.attached()))
	  {
		popXTservo1.attach(__POPXT_servo1);
	  }
	  popXTservo1.write(angle);

      if (!(popXTservo2.attached()))
	  {
		popXTservo2.attach(__POPXT_servo2);
	  }
	  popXTservo2.write(angle);

      if (!(popXTservo3.attached()))
	  {
		popXTservo3.attach(__POPXT_servo3);
	  }
	  popXTservo3.write(angle);
	}
  }
  if (servo==1)
  {
    if (angle==-1)
	{
	  popXTservo1.detach();
	}
	else
	{
      if (!(popXTservo1.attached()))
	  {
		popXTservo1.attach(__POPXT_servo1);
	  }
	  popXTservo1.write(angle);
	}
  }
  if (servo==2)
  {
    if (angle==-1)
	{
	  popXTservo2.detach();
	}
	else
	{
      if (!(popXTservo2.attached()))
	  {
		popXTservo2.attach(__POPXT_servo2);
	  }
	  popXTservo2.write(angle);
	}
  }
  if (servo==3)
  {
    if (angle==-1)
	{
	  popXTservo3.detach();
	}
	else
	{
      if (!(popXTservo3.attached()))
	  {
		popXTservo3.attach(__POPXT_servo3);
	  }
	  popXTservo3.write(angle);
	}
  }
}
#endif

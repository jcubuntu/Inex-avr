#ifndef _ATX2_SERVOMOTOR_H_
#define _ATX2_SERVOMOTOR_H_

#include "Servo.h"
#define __ATX2servo13 13
#define __ATX2servo14 14
#define __ATX2servo15 15
#include <ATX2_XIO.h> //

Servo ATX2servo1;
Servo ATX2servo2;
Servo ATX2servo3;

// servo 4,5,6,7,8 extended to XIO

void servo(uint8_t servo,signed int angle)
{

  if (servo==1)
  {
	if (angle==-1)
	{
	  ATX2servo1.detach();
	}
	else
	{
	  if (!(ATX2servo1.attached()))
	  {
		ATX2servo1.attach(__ATX2servo13);
	  }
	  ATX2servo1.write(angle);
	}
  }

  if (servo==2)
  {
	if (angle==-1)
	{
	  ATX2servo2.detach();
	}
	else
	{
	  if (!(ATX2servo2.attached()))
	  {
		ATX2servo2.attach(__ATX2servo14);
	  }
	  ATX2servo2.write(angle);
	}
  }

  if (servo==3)
  {
	if (angle==-1)
	{
	  ATX2servo3.detach();
	}
	else
	{
	  if (!(ATX2servo3.attached()))
	  {
		ATX2servo3.attach(__ATX2servo15);
	  }
	  ATX2servo3.write(angle);
	}
  }
  
  if (servo==4)
  {
	if (angle==-1)
	{
	// detach SV4
	  __XIOxfer(0x81,0xff,0x00,0xff);
	}
	else
	{
	  if (angle<0) angle=0;
	  if (angle>200) angle=200;
	// control SV4
	  __XIOxfer(0x81,angle,0x00,0xff);
	}
  }
  if (servo==5)
  {
	if (angle==-1)
	{
	// detach SV5
	  __XIOxfer(0x82,0xff,0x00,0xff);
	}
	else
	{
	  if (angle<0) angle=0;
	  if (angle>250) angle=250;
	// control SV5
	  __XIOxfer(0x82,angle,0x00,0xff);
	}
  }
  if (servo==6)
  {
	if (angle==-1)
	{
	// detach SV6
	  __XIOxfer(0x84,0xff,0x00,0xff);
	}
	else
	{
	  if (angle<0) angle=0;
	  if (angle>250) angle=250;
	// control SV6
	  __XIOxfer(0x84,angle,0x00,0xff);
	}
  }
  if (servo==7)
  {
	if (angle==-1)
	{
	// detach SV7
	  __XIOxfer(0x88,0xff,0x00,0xff);
	}
	else
	{
	  if (angle<0) angle=0;
	  if (angle>250) angle=250;
	// control SV7
	  __XIOxfer(0x88,angle,0x00,0xff);
	}
  }
  if (servo==8)
  {
	if (angle==-1)
	{
	// detach SV5
	  __XIOxfer(0x90,0xff,0x00,0xff);
	}
	else
	{
	  if (angle<0) angle=0;
	  if (angle>200) angle=200;
	// control SV8
	  __XIOxfer(0x90,angle,0x00,0xff);
	}
  }
}

#endif


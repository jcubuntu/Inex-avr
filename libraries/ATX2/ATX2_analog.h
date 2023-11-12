#ifndef _ATX2_ANALOG_H_
#define _ATX2_ANALOG_H_
// replace OLD macro with function
//#define knob() analog(7)

// replace OLD macro with function
#define sw_OK sw_ok
#define sw_OK_press	sw_ok_press

#include <ATX2_XIO.h> //

int __analogValue=0;
int __knobLastValue=0;

unsigned int analog(char ch)
{
  if (ch<8)
  {
    analogRead(ch);
    return(analogRead(ch));
  }
  else
  {
    // get data from XIO
    __XIOxfer(ch,0x00,0x00,0xff);
    __analogValue=(__XIO_dataByte0Response<<8)|__XIO_dataByte1Response;
    return(__analogValue);
  }
 }

int sw_OK(void)
{
//  __XIOxfer(0x02,0x00,0x00,0xff);
//  return(__XIO_dataByte1Response);
	bool OKpressed;
    __XIOxfer(13,0x00,0x00,0xff);
    __analogValue=(__XIO_dataByte0Response<<8)|__XIO_dataByte1Response;
    if (__analogValue<2)
    {
      OKpressed=true;
    }
    else
    {
       OKpressed=false;
    }
    
    return(OKpressed);
}

void sw_OK_press(void)
{
  while(!sw_OK())
  {
  }
  while(sw_OK())
  {
  }

}

unsigned int knob(void)
{
  __XIOxfer(13,0x00,0x00,0xff);
  __analogValue=(__XIO_dataByte0Response<<8)|__XIO_dataByte1Response;

      if (__analogValue>=8)
      {
        if (__analogValue<23)
          __analogValue=23;
  __knobLastValue=__analogValue-23;
      }  
  return(__knobLastValue);
}

int knob(int scale)
{
  long value;
  value=knob();
  value=((value*(scale+1))/1000);
  if (value>scale)
  {
    value=scale;
  }
  return(value);
}

int knob(int scaleCCW,int scaleCW)
{
  long value;
//  analogRead(7);
//  value=analogRead(7);
  value=knob();
  // unit in 1000 count
  
  if (scaleCW>=scaleCCW)
  {
	value=value/(1000/((scaleCW+1)-scaleCCW));
	value+=scaleCCW;
	if (value>scaleCW)
	{
	  value=scaleCW;
	}
  }
  else
  {
	value=1000-value;
	value=value/(1000/((scaleCCW+1)-scaleCW));
	value+=scaleCW;
	if (value>scaleCCW)
	{
	  value=scaleCCW;
	}
  }
  return(value);
}

#endif

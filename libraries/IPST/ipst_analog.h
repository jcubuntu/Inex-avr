#ifndef _IPST_ANALOG_H_
#define _IPST_ANALOG_H_
// replace OLD macro with function
//#define knob() analog(7)

// replace OLD macro with function
#define sw_OK sw_ok
#define sw_OK_press	sw_ok_press

unsigned int analog(char ch)
{
  analogRead(ch);
  return(analogRead(ch));         
}

#if defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) 
	unsigned int knob(void)
	{
	  analogRead(7);
	  return(analogRead(7));
	}

	int knob(int scale)
	{
	  long value;
	  analogRead(7);
	  value=analogRead(7);
	  value=((value*(scale+1))/1023);
	  if (value>scale)
	  {
		value=scale;
	  }
	  return(value);
	}

	int knob(int scaleCCW,int scaleCW)
	{
	  long value;
	  analogRead(7);
	  value=analogRead(7);
	  // unit in 1023 count
	  
	  if (scaleCW>=scaleCCW)
	  {
		value=value/(1023/((scaleCW+1)-scaleCCW));
		value+=scaleCCW;
		if (value>scaleCW)
		{
		  value=scaleCW;
		}
	  }
	  else
	  {
		value=1023-value;
		value=value/(1023/((scaleCCW+1)-scaleCW));
		value+=scaleCW;
		if (value>scaleCCW)
		{
		  value=scaleCCW;
		}
	  }
	  return(value);
	}

#else
	int __knobLastValue=0;
#if defined (_POPX2_H_)
	int sw_OK(void)
	{
	  analogRead(7);
	  return ((analogRead(7))<2);
	}

	void sw_OK_press(void)
	{
	  while(analogRead(7)>=2);
	  while(analogRead(7)<2);
	}

	unsigned int knob(void)
	{
	  int __knobValue;
	  analogRead(7);
	  __knobValue=analogRead(7);
	  if (__knobValue>=8)
	  {
		if (__knobValue<23)
		  __knobValue=23;
		__knobLastValue=__knobValue-23;
	  }
	  return(__knobLastValue);
	}

	int knob(int scale)
	{
	  long value;
	//  analogRead(7);
	//  value=analogRead(7);
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
#else
	// IPST-SE
	int sw_OK(void)
	{
	  return ((analogRead(7))<=10);
	}

	void sw_OK_press(void)
	{
	  while(analogRead(7)>10);
	  while(analogRead(7)<=10);
	}

	unsigned int knob(void)
	{
	  int __knobValue;
	  analogRead(7);
	  __knobValue=analogRead(7);
	  if (__knobValue>64)
	  {
		__knobLastValue=__knobValue;
	  }
	  return(__knobLastValue);
	}

	int knob(int scale)
	{
	  long value;
	//  analogRead(7);
	//  value=analogRead(7);
	  value=knob();
	  if (value<123)
	  {
		value=123;
	  }
	  value-=123;
	  // unit in 900 count
	  value=((value*(scale+1))/900);
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
	  if (value<123)
	  {
		value=123;
	  }
	  value-=123;
	  // unit in 900 count
	  
	  if (scaleCW>=scaleCCW)
	  {
		value=value/(900/((scaleCW+1)-scaleCCW));
		value+=scaleCCW;
		if (value>scaleCW)
		{
		  value=scaleCW;
		}
	  }
	  else
	  {
		value=900-value;
		value=value/(900/((scaleCCW+1)-scaleCW));
		value+=scaleCW;
		if (value>scaleCCW)
		{
		  value=scaleCCW;
		}
	  }
	  return(value);
	}
#endif
#endif
#endif

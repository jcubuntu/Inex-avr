#ifndef _IPST_SERVOMOTOR_H_
#define _IPST_SERVOMOTOR_H_

#if defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) 

// Update 06/08/2014 : Add alias number of digital pin to servo


	#include "ipst_SoftwareServo.h"

	#define SERVO_B0 0
	#define SERVO_B1 1
	#define SERVO_B2 2
	#define SERVO_B3 3
	#define SERVO_B4 4

	#define SERVO_D15 15
	#define SERVO_D14 14
	#define SERVO_D13 13
	#define SERVO_D12 12

	#define __IPSTservo16 16
	#define __IPSTservo17 17
	#define __IPSTservo18 18
	#define __IPSTservo19 19
	#define __IPSTservo20 20

	ipst_SoftwareServo servo0;
	ipst_SoftwareServo servo1;
	ipst_SoftwareServo servo2;
	ipst_SoftwareServo servo3;
	ipst_SoftwareServo servo4;

	void servoSleep(void)
	{
	  ipst_SoftwareServo::refresh();
	}

	void servoSleep(unsigned int time)
	{
	  int j;
	  j=time>>4;

	  ipst_SoftwareServo::refresh();
	  while (j-->0)
	  {
		delay(16);
		ipst_SoftwareServo::refresh();
	  }
	  delay((time&0x000f));
	}

	void servoRefresh()
	{
	  int i;
	  for (i=0;i<25;i++)
	  {
		delay(20);
		ipst_SoftwareServo::refresh();
	  }
	}
	

	void servo(uint8_t servo,uint8_t angle)
	{
	  if ((servo==SERVO_B0)||(servo==SERVO_D15))
	  {
		if (angle==-1)
		{
		  servo0.detach();
		}
		else
		{
		  if (!(servo0.attached()))
		  {
			servo0.attach(__IPSTservo16);
			servo0.setMaximumPulse(2200);
		  }
		  servo0.write(angle);
		}
	  }

	  if ((servo==SERVO_B1)||(servo==SERVO_D14))
	  {
		if (angle==-1)
		{
		  servo1.detach();
		}
		else
		{
		  if (!(servo1.attached()))
		  {
			servo1.attach(__IPSTservo17);
			servo1.setMaximumPulse(2200);
		  }
		  servo1.write(angle);
		}
	  }

	  if ((servo==SERVO_B2)||(servo==SERVO_D13))
	  {
		if (angle==-1)
		{
		  servo2.detach();
		}
		else
		{
		  if (!(servo2.attached()))
		  {
			servo2.attach(__IPSTservo18);
			servo2.setMaximumPulse(2200);
		  }
		  servo2.write(angle);
		}
	  }

	  if ((servo==SERVO_B3)||(servo==SERVO_D12))
	  {
		if (angle==-1)
		{
		  servo3.detach();
		}
		else
		{
		  if (!(servo3.attached()))
		  {
			servo3.attach(__IPSTservo19);
			servo3.setMaximumPulse(2200);
		  }
		  servo3.write(angle);
		}
	  }

	  if (servo==SERVO_B4)
	  {
		if (angle==-1)
		{
		  servo4.detach();
		}
		else
		{
		  if (!(servo4.attached()))
		  {
			servo4.attach(__IPSTservo20);
			servo4.setMaximumPulse(2200);
		  }
		  servo4.write(angle);
		}
	  }
	}

/*
	char servo_ini = 0;
	unsigned char activeServo[5]={0,0,0,0,0};
	unsigned char timeBaseServo[5]={0,0,0,0,0};
	unsigned long timerTick=0;

	ISR(TIMER2_OVF_vect)
	{
		//TCNT0 = 156;	// Reload Interval 50 us  
		TCNT2 = 206;	// Reload Interval 25 us  
		timerTick++;
		if(timerTick>=1000)
		{
			timerTick = 0;
		}
		if(activeServo[0]==1)
		{
			if(timerTick<=timeBaseServo[0])
				PORTB |= 0x01;
			else
				PORTB &= 0xFE;
		}
		if(activeServo[1]==1)
		{
			if(timerTick<=timeBaseServo[1])
				PORTB |= 0x02;
			else
				PORTB &= 0xFD;
		}
		if(activeServo[2]==1)
		{
			if(timerTick<=timeBaseServo[2])
				PORTB |= 0x04;
			else
				PORTB &= 0xFB;
		}
		if(activeServo[3]==1)
		{
			if(timerTick<=timeBaseServo[3])
				PORTB |= 0x08;
			else
				PORTB &= 0xF7;
		}
		if(activeServo[4]==1)
		{
			if(timerTick<=timeBaseServo[4])
				PORTB |= 0x10;
			else
				PORTB &= 0xEF;
		}
	}
	void servo_start(void) // Config. and Start up timer 0 
	{
	   
		TCCR2 = (1<<CS21); 	// Prescaler 8,16 MHz,1 MC = 8/16M = 0.5 us/count 
		TIFR |= 1<<TOV2; 	//Clear TOV0 / clear
		TIMSK |= 1<<TOIE2; 	//Enable Timer0 Overflow Interrupt
		//TCNT0 = 156;	// Interval 50 us  	
		TCNT2 = 206;	// Interval 50 us  	
		
		sei();	// Enable all interrupt
		timerTick = 0;
		servo_ini = 1;
	}
	void servo_stop()
	{
		TCCR2 = 0;		// Stop timer and 
		TCNT2 = 0;
		TIMSK &= ~_BV(TOIE2);	
		timerTick = 0;
		servo_ini = 0;
	}
	void servo(unsigned char _ch,unsigned int _pos)
	{
		if(servo_ini==0)
		{
			servo_start();
			servo_ini=1;
		}
		if(_ch>=0 && _ch<=4)
		{
			DDRB |= 1<<(_ch);
			timeBaseServo[_ch] = _pos;
			activeServo[_ch]=1;
		}
	}
	void servo_pause(char _ch)
	{
		if(_ch>=0 && _ch<=4)
		{
			activeServo[_ch]=0;
		}
	}
	void servo_resume(char _ch)
	{
		if(_ch>=0 && _ch<=4)
		{
			activeServo[_ch]=1;
		}
	}
	unsigned char servo_get_status(char _ch)
	{
		return(activeServo[_ch]);
	}
*/


#else
	#include "Servo.h"
	// flags for function set
  #if defined (_POPX2_H_)

	#define SERVO_B1 1
	#define SERVO_B2 2
	#define SERVO_B3 3
	#define __IPSTservo13 13
	#define __IPSTservo14 14
	#define __IPSTservo15 15

	Servo IPSTservo13;
	Servo IPSTservo14;
	Servo IPSTservo15;

	void servo(uint8_t servo,signed int angle)
	{
	  if (servo==SERVO_B1)
	  {
		if (angle==-1)
		{
		  IPSTservo13.detach();
		}
		else
		{
		  if (!(IPSTservo13.attached()))
		  {
			IPSTservo13.attach(__IPSTservo13);
		  }
		  IPSTservo13.write(angle);
		}
	  }

	  if (servo==SERVO_B2)
	  {
		if (angle==-1)
		{
		  IPSTservo14.detach();
		}
		else
		{
		  if (!(IPSTservo14.attached()))
		  {
			IPSTservo14.attach(__IPSTservo14);
		  }
		  IPSTservo14.write(angle);
		}
	  }

	  if (servo==SERVO_B3)
	  {
		if (angle==-1)
		{
		  IPSTservo15.detach();
		}
		else
		{
		  if (!(IPSTservo15.attached()))
		  {
			IPSTservo15.attach(__IPSTservo15);
		  }
		  IPSTservo15.write(angle);
		}
	  }
	}

  #else

	#define SERVO_B0 0
	#define SERVO_B1 1
	#define SERVO_B2 2
	#define SERVO_B3 3
	#define __IPSTservo12 12
	#define __IPSTservo13 13
	#define __IPSTservo14 14
	#define __IPSTservo15 15

	Servo IPSTservo12;
	Servo IPSTservo13;
	Servo IPSTservo14;
	Servo IPSTservo15;

	void servo(uint8_t servo,signed int angle)
	{
	  if (servo==SERVO_B3)
	  {
		if (angle==-1)
		{
		  IPSTservo12.detach();
		}
		else
		{
		  if (!(IPSTservo12.attached()))
		  {
			IPSTservo12.attach(__IPSTservo12);
		  }
		  IPSTservo12.write(angle);
		}
	  }

	  if (servo==SERVO_B2)
	  {
		if (angle==-1)
		{
		  IPSTservo13.detach();
		}
		else
		{
		  if (!(IPSTservo13.attached()))
		  {
			IPSTservo13.attach(__IPSTservo13);
		  }
		  IPSTservo13.write(angle);
		}
	  }

	  if (servo==SERVO_B1)
	  {
		if (angle==-1)
		{
		  IPSTservo14.detach();
		}
		else
		{
		  if (!(IPSTservo14.attached()))
		  {
			IPSTservo14.attach(__IPSTservo14);
		  }
		  IPSTservo14.write(angle);
		}
	  }

	  if (servo==SERVO_B0)
	  {
		if (angle==-1)
		{
		  IPSTservo15.detach();
		}
		else
		{
		  if (!(IPSTservo15.attached()))
		  {
			IPSTservo15.attach(__IPSTservo15);
		  }
		  IPSTservo15.write(angle);
		}
	  }
	}
  #endif
#endif
#endif


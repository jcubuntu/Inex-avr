//------------------------------------------------------------------------------------------------//
// Program	: Library Read/Write digital I/O   
// Description 	: Library Read/Write digital I/O 
// Frequency	: Crytal 16 MHz  
// Filename	: in_out.h
// C compiler	: Wirring
//------------------------------------------------------------------------------------------------//
#ifndef _IPST_IN_OUT_H_
#define _IPST_IN_OUT_H_

#include <avr/io.h>
	
#define set_a(x)  		DDRA |= _BV(x);	PORTA |= _BV(x);		
#define clear_a(x)   	DDRA |= _BV(x);	PORTA &= ~_BV(x);	
#define set_b(x)  		DDRB |= _BV(x); PORTB |= _BV(x);	
#define clear_b(x) 		DDRB |= _BV(x); PORTB &= ~_BV(x);		
#define set_c(x)  		DDRC |= _BV(x);	PORTC |= _BV(x)		
#define clear_c(x)   	DDRC |= _BV(x);	PORTC &= ~_BV(x);		
#define set_d(x)  		DDRD |= _BV(x);	PORTD |= _BV(x)		
#define clear_d(x)   	DDRD |= _BV(x);	PORTD &= ~_BV(x);		

// replace OLD macro with function
//#define sw1() (in_b(6)==0)
//#define sw1_press() while(in_b(6)); while(in_b(6)==0);

void toggle_a(char x)
{
	DDRA |= _BV(x); 
	PORTA ^= _BV(x);
}
void toggle_b(char x)
{
	DDRB |= _BV(x); 
	PORTB ^= _BV(x);
}
void toggle_c(char x)
{
	DDRC |= _BV(x); 
	PORTC ^= _BV(x);
}
void toggle_d(char x)
{
	DDRD |= _BV(x); 
	PORTD ^= _BV(x);
}

char in_a(char _bit)
{
	DDRA &= ~(1<<_bit);
	return((PINA & _BV(_bit))>>_bit);	
}
char in_b(char _bit)
{
	DDRB &= ~(1<<_bit);
	return((PINB & _BV(_bit))>>_bit);	
}
char in_c(char _bit)
{
	DDRC &= ~(1<<_bit);
	return((PINC & _BV(_bit))>>_bit);	
}
char in_d(char _bit)
{
	DDRD &= ~(1<<_bit);
	return((PIND & _BV(_bit))>>_bit);	
}


void out_a(char _bit,char _dat)
{
	DDRA |= _BV(_bit);
	if(_dat)
		PORTA |= _BV(_bit);
	else
		PORTA &= ~_BV(_bit);

}
void out_b(char _bit,char _dat)
{
	DDRB |= _BV(_bit);
	if(_dat)
		PORTB |= _BV(_bit);
	else
		PORTB &= ~_BV(_bit);

}
void out_c(char _bit,char _dat)
{
	DDRC |= _BV(_bit);
	if(_dat)
		PORTC |= _BV(_bit);
	else
		PORTC &= ~_BV(_bit);

}
void out_d(char _bit,char _dat) 
{
	DDRD |= _BV(_bit);
	if(_dat)
		PORTD |= _BV(_bit);
	else
		PORTD &= ~_BV(_bit);
	
}

void out(int num,int _dat)
{
     pinMode(num, OUTPUT); 
     digitalWrite(num,_dat);
}
int in(int num)
{
     pinMode(num,INPUT); 
     return(digitalRead(num));
}

#if defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) 
	int sw1()
	{
	  return (in_b(5)==0);
	}

	void sw1_press(void)
	{
	  while(in_b(5));
	  while(in_b(5)==0);
	}

	int sw2()
	{
	  return (in_b(6)==0);
	}

	void sw2_press(void)
	{
	  while(in_b(6));
	  while(in_b(6)==0);
	}

	int sw3()
	{
	  return (in_b(7)==0);
	}

	void sw3_press(void)
	{
	  while(in_b(7));
	  while(in_b(7)==0);
	}

#else
	int sw1()
	{
	  return (in_b(6)==0);
	}

	int sw_1()
	{
	  return (in_b(6)==0);
	}

	void sw1_press(void)
	{
	  while(in_b(6));
	  while(in_b(6)==0);
	}

	void sw_1_press(void)
	{
	  while(in_b(6));
	  while(in_b(6)==0);
	}
#endif

#endif
//------------------------------------------------------------------------------------------------//
// Program	: Library Read/Write digital I/O   
// Description 	: Library Read/Write digital I/O 
// Frequency	: Crytal 16 MHz  
// Filename	: in_out.h
// C compiler	: Wirring
//------------------------------------------------------------------------------------------------//
#ifndef _IN_OUT_H_
#define _IN_OUT_H_
#include "pins_arduino.h"
#include "wiring_private.h"

//#include <avr/io.h>
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
#endif





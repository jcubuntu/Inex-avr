/*
  Servo.h - Servo library for Arduino & Wiring
  Based on Hernando Barragan's original C implementation
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _Smotor_H_
#define _Smotor_H_

#include <inttypes.h>
#include <avr/interrupt.h>

class Smotor
{
  private:
    uint8_t pin;
    uint8_t angle;       // in degrees
    uint16_t pulse0;     // pulse width in TCNT0 counts
    uint8_t min16;       // minimum pulse, 16uS units  (default is 34)
    uint8_t max16;       // maximum pulse, 16uS units, 0-4ms range (default is 150)
    class Smotor *next;
    static Smotor* first;
  public:
    Smotor();
    uint8_t attach(int);     // attach to a pin, sets pinMode, returns 0 on failure, won't
                             // position the servo until a subsequent write() happens
    void detach();
    void write(int);         // specify the angle in degrees, 0 to 180
    uint8_t read();
    uint8_t attached();
    void setMinimumPulse(uint16_t);  // pulse length for 0 degrees in microseconds, 540uS default
    void setMaximumPulse(uint16_t);  // pulse length for 180 degrees in microseconds, 2400uS default
    static void refresh();    // must be called at least every 50ms or so to keep servo alive
                              // you can call more often, it won't happen more than once every 20ms
};

/*#include "WProgram.h"

extern "C" {
//  #include <stdio.h>
//  #include <inttypes.h>
//  #include <avr/interrupt.h>
//  #include <avr/pgmspace.h>
//  #include <stdio.h>
//  #include <stdarg.h>
//  #include <math.h>
  
//  #include "WConstants.h"
  
  extern void pinMode(uint8_t, uint8_t);
  //extern uint8_t digitalRead(uint8_t);
  extern void digitalWrite(uint8_t, uint8_t);

 }*/


Smotor *Smotor::first;

#define NO_ANGLE (0xff)

Smotor::Smotor() : pin(0),angle(NO_ANGLE),pulse0(0),min16(34),max16(150),next(0)
{}

void Smotor::setMinimumPulse(uint16_t t)
{
    min16 = t/16;
}

void Smotor::setMaximumPulse(uint16_t t)
{
    max16 = t/16;
}

uint8_t Smotor::attach(int pinArg)
{
    pin = pinArg;
    angle = NO_ANGLE;
    pulse0 = 0;
    next = first;
    first = this;
    digitalWrite(pin,0);
    pinMode(pin,OUTPUT);
    return 1;
}

void Smotor::detach()
{
    for ( Smotor **p = &first; *p != 0; p = &((*p)->next) ) {
	if ( *p == this) {
	    *p = this->next;
	    this->next = 0;
	    return;
	}
    }
}

void Smotor::write(int angleArg)
{
    if ( angleArg < 0) angleArg = 0;
    if ( angleArg > 180) angleArg = 180;
    angle = angleArg;
    // bleh, have to use longs to prevent overflow, could be tricky if always a 16MHz clock, but not true
    // That 64L on the end is the TCNT0 prescaler, it will need to change if the clock's prescaler changes,
    // but then there will likely be an overflow problem, so it will have to be handled by a human.
    pulse0 = (min16*16L*clockCyclesPerMicrosecond() + (max16-min16)*(16L*clockCyclesPerMicrosecond())*angle/180L)/64L;
}

uint8_t Smotor::read()
{
    return angle;
}

uint8_t Smotor::attached()
{
    for ( Smotor *p = first; p != 0; p = p->next ) {
	if ( p == this) return 1;
    }
    return 0;
}

void Smotor::refresh()
{
    uint8_t count = 0, i = 0;
    uint16_t base = 0;
    Smotor *p;
    static unsigned long lastRefresh = 0;
    unsigned long m = millis();

    // if we haven't wrapped millis, and 20ms have not passed, then don't do anything
    if ( m >= lastRefresh && m < lastRefresh + 20) return;
    lastRefresh = m;

    for ( p = first; p != 0; p = p->next ) if ( p->pulse0) count++;
    if ( count == 0) return;

    // gather all the SoftwareServos in an array
    Smotor *s[count];
    for ( p = first; p != 0; p = p->next ) if ( p->pulse0) s[i++] = p;

    // bubblesort the SoftwareServos by pulse time, ascending order
    for(;;) {
	uint8_t moved = 0;
	for ( i = 1; i < count; i++) {
	    if ( s[i]->pulse0 < s[i-1]->pulse0) {
		Smotor *t = s[i];
		s[i] = s[i-1];
		s[i-1] = t;
		moved = 1;
	    }
	}
	if ( !moved) break;
    }

    // turn on all the pins
    // Note the timing error here... when you have many SoftwareServos going, the
    // ones at the front will get a pulse that is a few microseconds too long.
    // Figure about 4uS/SoftwareServo after them. This could be compensated, but I feel
    // it is within the margin of error of software SoftwareServos that could catch
    // an extra interrupt handler at any time.
    for ( i = 0; i < count; i++) digitalWrite( s[i]->pin, 1);

    uint8_t start = TCNT0;
    uint8_t now = start;
    uint8_t last = now;

    // Now wait for each pin's time in turn..
    for ( i = 0; i < count; i++) {
	uint16_t go = start + s[i]->pulse0;

	// loop until we reach or pass 'go' time
	for (;;) {
	    now = TCNT0;
	    if ( now < last) base += 256;
	    last = now;

	    if ( base+now > go) {
		digitalWrite( s[i]->pin,0);
		break;
	    }
	}
    }
}
#endif


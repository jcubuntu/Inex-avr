#ifndef _ATX2_SONAR_H_
#define _ATX2_SONAR_H_

/*
  Original from Ultrasonic.cpp - Library for HC-SR04 Ultrasonic Ranging Module.library

  Created by ITead studio. Apr 20, 2010.
  iteadstudio.com
  
  ATX2_sonar.h was simplify to ATX2-SE board
  
*/

#if defined(ARDUINO) || (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

int Trig_pin=24;
int Echo_pin=25;
long  duration;
unsigned int distance_cm;

unsigned int sonarTime()
{
  pinMode(Trig_pin,OUTPUT);
  pinMode(Echo_pin,INPUT);

  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH,23200);
  if (duration==0)
  {
    duration=23200;
  }
  return duration;
}

unsigned int __sonarTime()
{
  return sonarTime();
}

unsigned int sonar(void)
{
  sonarTime();
  if (duration==23200)
  {
    distance_cm = 400 ;
  }
  else
  {
    distance_cm = (duration /29) >> 1 ;
  }
  return distance_cm;
}

unsigned int sonar(int TP,int EP)
{
  Trig_pin=TP;
  Echo_pin=EP;
  return sonar();
}


#endif
/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "pins_arduino.h"
#include "ATX2_SPI.h"

ATX2_SPIClass ATX2_SPI;

void ATX2_SPIClass::begin() {
  // Set direction register for SCK and MOSI pin.
  // MISO pin automatically overrides to INPUT.
  // When the SS pin is set as OUTPUT, it can be used as
  // a general purpose output port (it doesn't influence
  // SPI operations).

  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);

  digitalWrite(SS, HIGH);
  pinMode(SS, OUTPUT);
  digitalWrite(SS, LOW);
  
  digitalWrite(SCK, LOW);
  digitalWrite(MOSI, LOW);

  // Warning: if the SS pin ever becomes a LOW INPUT then SPI 
  // automatically switches to Slave, so the data direction of 
  // the SS pin MUST be kept as OUTPUT.
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
}

void ATX2_SPIClass::end() {
  SPCR &= ~_BV(SPE);
}

void ATX2_SPIClass::setBitOrder(uint8_t bitOrder)
{
  if(bitOrder == LSBFIRST) {
    SPCR |= _BV(DORD);
  } else {
    SPCR &= ~(_BV(DORD));
  }
}

void ATX2_SPIClass::setDataMode(uint8_t mode)
{
  SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}

void ATX2_SPIClass::setClockDivider(uint8_t rate)
{
  SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
  SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((rate >> 2) & SPI_2XCLOCK_MASK);
}


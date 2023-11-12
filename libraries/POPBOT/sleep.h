#ifndef _SLEEP_H_
#define _SLEEP_H_
#define sleep(x) delay(x)
#include <util/delay.h>
void delay_us(unsigned int time)
{
  while(time-->0)
  {
    _delay_us(1.0);
  }
}
#endif



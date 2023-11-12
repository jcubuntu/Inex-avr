/*--------------------------------------------------------------------------*/
// Filename			: gp2d120_lib.h
// C compiler		: avr-gcc
/*--------------------------------------------------------------------------*/

#ifndef _GP2D120_LIB_H_
#define _GP2D120_LIB_H_

#include "analog.h"
#define _m 2933
#define _b 20
#define _k 1
unsigned int getdist(char adc_ch)
{
	unsigned int dist = 0;
    dist = (_m/(analog(adc_ch)+_b)) - _k;
	return(dist);
}

#endif

/*--------------------------------------------------------------------------*/
// Filename			: atx2_gp2d120.h
// C compiler		: avr-gcc
/*--------------------------------------------------------------------------*/

#ifndef _ATX2_GP2D120_H_
#define _ATX2_GP2D120_H_

#include "ATX2_analog.h"
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

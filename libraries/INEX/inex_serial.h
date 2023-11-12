#ifndef _INEX_SERIAL_H_
#define _INEX_SERIAL_H_
//-------------------- Condition  test parameter data type for display ---------------//
#ifndef TEST_CHAR_TYPE(x)
#define TEST_CHAR_TYPE(x) *x=='%' && (*(x+1)=='c' || *(x+1)=='C')
#endif

#ifndef TEST_BIN_TYPE(x)
#define TEST_BIN_TYPE(x) *x=='%' && (*(x+1)=='b' || *(x+1)=='B')
#endif

#ifndef TEST_HEX_TYPE(x)
#define TEST_HEX_TYPE(x) *x=='%' && (*(x+1)=='h' || *(x+1)=='H')
#endif

#ifndef TEST_INT_TYPE(x)
#define TEST_INT_TYPE(x) *x=='%' && (*(x+1)=='d' || *(x+1)=='D')
#endif

#ifndef TEST_LONG_TYPE(x)
#define TEST_LONG_TYPE(x) *x=='%' && (*(x+1)=='l' || *(x+1)=='L')
#endif

#ifndef TEST_FLOAT_TYPE(x)
#define TEST_FLOAT_TYPE(x) *x=='%' && (*(x+1)=='f' || *(x+1)=='F')
#endif

#ifndef TEST_STRING_TYPE(x)
#define TEST_STRING_TYPE(x) *x=='%' && (*(x+1)=='s' || *(x+1)=='S')
#endif

#ifndef SET_FLOAT_PREC
#define SET_FLOAT_PREC 1
unsigned int _floatPrecision=3;
void setFloatPrecision(unsigned int prec)
{
	_floatPrecision=prec;
}
#endif


//extern "C" {
//#include <HardwareSerial.h>
//}

#if !defined (_UNICON_H_) && !defined (_POPXT_H_)
extern HardwareSerial Serial;
#endif
unsigned long _baud=9600;
char uart_ini=0;

#if !defined (__AVR_ATmega16__) && !defined (__AVR_ATmega32__) 
extern HardwareSerial Serial1;
unsigned long _baud1=9600;
char uart1_ini=0;
#endif

//------------------------------------------------------------------
// for UART0 Communication                                                             
//------------------------------------------------------------------
void uart_set_baud(unsigned long baud) 
{
     _baud = baud;
     Serial.begin(baud);
	 uart_ini=1;
}
unsigned int uart_get_baud()
{
	return(_baud);
}
void uart_putc(unsigned char c) 
{
   	if(uart_ini==0)
	{
		uart_ini=1;
		uart_set_baud(_baud);
	}
    Serial.write(c);
}
void uart_write(unsigned char c) 
{
   	if(uart_ini==0)
	{
		uart_ini=1;
		uart_set_baud(_baud);
	}
    Serial.write(c);
}
void uart_puts(char *s) 
{
	while (*s) 
	{
		uart_putc(*s);
		s++;
	}
}
void uart(char *p,...) 
{
	char *arg,**pp;	// Poter of point
	char *ptr,buff[16]/*,s_arg_offset=0,s_arg_i=0*/;
	pp = &p;
	ptr = p;	// Copy address
	arg = (char *)pp;	// Copy address of p point	
	
	arg += 2;	// Cross 2 time go to Origin of first parameter 
	
	if(uart_ini==0)
	{
		uart_ini=1;
		uart_set_baud(_baud);
	}
		
	while(*ptr)                 // Check data pointer = 0?
	{
	 	if(TEST_CHAR_TYPE(ptr))
		{
			uart_putc(toascii(*arg));
			arg+=2;	// Cross address char type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_BIN_TYPE(ptr))
		{
			p = ultoa(*(unsigned int *)arg,&buff[0],2);
			uart_puts(p);
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_HEX_TYPE(ptr))
		{
			p = ultoa(*(unsigned int *)arg,&buff[0],16);
			uart_puts(p);
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_INT_TYPE(ptr))
		{
			p = ltoa(*(int *)arg,&buff[0],10);
			uart_puts(p);
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_LONG_TYPE(ptr))
		{
			p = ltoa(*(long *)arg,&buff[0],10);
			uart_puts(p);
			arg+=4;	// Cross address long type
			ptr++;	// Cross %l parameter
		}
		else if(TEST_FLOAT_TYPE(ptr))
		{
			p = dtostrf(*(float *)arg,2,_floatPrecision,&buff[0]);	// Convert float to string(used libm.a)
			uart_puts(p);
			arg+=4;	// Cross address long type
			ptr++;	// Cross %l parameter
		}
		else
		{
			uart_putc(*ptr);             // Send data to LCD
	 	}
		
		ptr++;                      // Increase address 1 time 
	}
}
unsigned char uart_available()
{
    if(uart_ini==0)
	{
		uart_ini=1;
		uart_set_baud(_baud);
	}
     return(Serial.available());    
}
int uart_getkey()
{
    if(uart_ini==0)
	{
		uart_ini=1;
		uart_set_baud(_baud);
	}
    return(Serial.read());    
}
int uart_ready()
{
    if(uart_ini==0)
	{
		uart_ini=1;
		uart_set_baud(_baud);
	}
     return(Serial.available());    
}
int uart_read()
{
    if(uart_ini==0)
	{
		uart_ini=1;
		uart_set_baud(_baud);
	}
    return(Serial.read());    
}
void uart_flush()
{
 Serial.flush();
}

#if !defined (__AVR_ATmega16__) && !defined (__AVR_ATmega32__) 
//------------------------------------------------------------------
// for UART1 Communication                                                             
//------------------------------------------------------------------
void uart1_set_baud(unsigned long baud) 
{
     _baud1 = baud;
     Serial1.begin(baud);
	 uart1_ini=1;
}
unsigned int uart1_get_baud()
{
	return(_baud1);
}
void uart1_putc(unsigned char c) 
{
   	if(uart1_ini==0)
	{
		uart1_ini=1;
		uart1_set_baud(_baud1);
	}
    Serial1.write(c);
}
void uart1_write(unsigned char c) 
{
   	if(uart1_ini==0)
	{
		uart1_ini=1;
		uart1_set_baud(_baud1);
	}
    Serial1.write(c);
}
void uart1_puts(char *s) 
{
	while (*s) 
	{
		uart1_putc(*s);
		s++;
	}
}
void uart1(char *p,...) 
{
	char *arg,**pp;	// Poter of point
	char *ptr,buff[16]/*,s_arg_offset=0,s_arg_i=0*/;
	pp = &p;
	ptr = p;	// Copy address
	arg = (char *)pp;	// Copy address of p point	
	
	arg += 2;	// Cross 2 time go to Origin of first parameter 
	
	if(uart_ini==0)
	{
		uart1_ini=1;
		uart1_set_baud(_baud1);
	}
		
	while(*ptr)                 // Check data pointer = 0?
	{
	 	if(TEST_CHAR_TYPE(ptr))
		{
			uart1_putc(toascii(*arg));
			arg+=2;	// Cross address char type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_BIN_TYPE(ptr))
		{
			p = ultoa(*(unsigned int *)arg,&buff[0],2);
			uart1_puts(p);
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_HEX_TYPE(ptr))
		{
			p = ultoa(*(unsigned int *)arg,&buff[0],16);
			uart1_puts(p);
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_INT_TYPE(ptr))
		{
			p = ltoa(*(int *)arg,&buff[0],10);
			uart1_puts(p);
			arg+=2;	// Cross address int type
			ptr++;	// Cross %d parameter
		}
		else if(TEST_LONG_TYPE(ptr))
		{
			p = ltoa(*(long *)arg,&buff[0],10);
			uart1_puts(p);
			arg+=4;	// Cross address long type
			ptr++;	// Cross %l parameter
		}
		else if(TEST_FLOAT_TYPE(ptr))
		{
			p = dtostrf(*(float *)arg,2,_floatPrecision,&buff[0]);	// Convert float to string(used libm.a)
			uart1_puts(p);
			arg+=4;	// Cross address long type
			ptr++;	// Cross %l parameter
		}
		else
		{
			uart1_putc(*ptr);             // Send data to LCD
	 	}
		
		ptr++;                      // Increase address 1 time 
	}
}
unsigned char uart1_available()
{
    if(uart1_ini==0)
	{
		uart1_ini=1;
		uart1_set_baud(_baud1);
	}
     return(Serial1.available());    
}
int uart1_getkey()
{
    if(uart1_ini==0)
	{
		uart1_ini=1;
		uart1_set_baud(_baud1);
	}
    return(Serial1.read());    
}
int uart1_ready()
{
    if(uart1_ini==0)
	{
		uart1_ini=1;
		uart1_set_baud(_baud1);
	}
     return(Serial1.available());    
}
int uart1_read()
{
    if(uart1_ini==0)
	{
		uart1_ini=1;
		uart1_set_baud(_baud1);
	}
    return(Serial1.read());    
}

void uart1_flush()
{
 Serial1.flush();
}
#endif
#endif



//------------------------------------------------------------------------------------//
// Program		: Library for i2c bus   
// Description 	: Library for i2c bus(TWI)
// Frequency	: Crystal 16 MHz 
// Filename		: i2c.h
// C compiler	: WinAVR
//------------------------------------------------------------------------------------//
#ifndef _COMPASS_I2C_H_
#define _COMPASS_I2C_H_

#include <avr/io.h>	// Header file for AVR MCU 
#include <util/twi.h>	// Include Library for TW interface	
#define ACK		1	// Macro for used acknowledge in i2c_read function
#define NACK	0	// Macro for not used acknowledge in i2c_read function

#ifndef	TWSR
#define TWSR		TWSR0
#endif

#ifndef	TWCR
#define TWCR		TWCR0
#endif

#ifndef	TWDR
#define TWDR		TWDR0
#endif

#ifndef	TWBR
#define TWBR		TWBR0
#endif

//----------------------------------------------------------------------------//
//---------------------- Function i2c start condition  -----------------------//
//----------------------------------------------------------------------------//
char i2c_start()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);	// Generate start condition
	while (!(TWCR & (1 << TWINT))); // Wait until complete
	if(TW_STATUS==TW_MT_ARB_LOST)	// Check status for success?
	{
		return -1;
	}
	else 
	{
		return 0;
	}
}
//----------------------------------------------------------------------------//
//---------------------- Function i2c stop condition  -----------------------//
//----------------------------------------------------------------------------//
void i2c_stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);	// Generate stop condition
}
//----------------------------------------------------------------------------//
//---------------------- Function i2c write data  ----------------------------//
//----------------------------------------------------------------------------//
char i2c_write(unsigned char dat)
{
	TWDR = dat;	// Load data to send via i2c bus
	TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);	// Transfer data used acknowledge
	//TWCR = (1 << TWINT) | (1 << TWEN); //For not used acknowledge
	while (!(TWCR & (1 << TWINT)));	// Wait until complete
	if(TW_STATUS==TW_MT_ARB_LOST)	// Check status for success?
	{
		return -1;
	}
	else 
	{
		return 0;
	}
}
//----------------------------------------------------------------------------//
//---------------------- Function i2c read data  -----------------------------//
//----------------------------------------------------------------------------//
unsigned char i2c_read(char ack)
{
	if(ack)
	{
		TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);	// For used acknowledge
	}
	else
	{
		TWCR = (1 << TWINT) | (1 << TWEN);	//   For not used acknowledge
	}
	while (!(TWCR & (1 << TWINT)));	// Wait until data complete
	return(TWDR);	// Return data 
}

#endif
#ifndef _NUNCHUK_H_
#define _NUNCHUK_H_

#include <i2c.h>
#include <sleep.h>

#define NUNCHUK_ID 0xA4

unsigned char __outbuf[6];		// array to store arduino output
char _nunchuk_ini = 0;

void nunchuk_init ()
{
  	TWBR = 60;	// Ensure decrease bit rate i2c bus
	i2c_start();
	i2c_write(NUNCHUK_ID);
	i2c_write(0xF0);
	i2c_write(0x55);
	i2c_stop();
	i2c_start();
	i2c_write(NUNCHUK_ID);
	i2c_write(0xFB);
	i2c_write(0x00);
	i2c_stop();
}

void nunchuk_getData()
{
	if(_nunchuk_ini==0)
	{
		nunchuk_init();
		_nunchuk_ini=1;
	}
	i2c_start();		// Start condition
	i2c_write(NUNCHUK_ID);	// Send MCP23016 ID 
	i2c_write(0x00);	// Send MCP23016 ID 
	i2c_stop();		// Start condition
	
	i2c_start();	// Restart condition
	i2c_write(NUNCHUK_ID+1);	// Send MCP23016 ID for Read mode	
	__outbuf[0] = i2c_read(ACK);	// Read GP1 from MCP23016
	__outbuf[1] = i2c_read(ACK);	// Read GP1 from MCP23016
	__outbuf[2] = i2c_read(ACK);	// Read GP1 from MCP23016
	__outbuf[3] = i2c_read(ACK);	// Read GP1 from MCP23016
	__outbuf[4] = i2c_read(ACK);	// Read GP1 from MCP23016
	__outbuf[5] = i2c_read(NACK);	// Read GP1 from MCP23016
	i2c_stop();			// Stop condition
}
int nunchuk_zButton()	
{
	int z_button = 0;
	nunchuk_getData();
	if ((__outbuf[5] >> 0) & 1)
  	{
    	z_button = 1;
  	}
	return(z_button);	// Return 0 when z Button pressed
}
int nunchuk_cButton()	
{
	int c_button = 0;
	nunchuk_getData();
	if ((__outbuf[5] >> 1) & 1)
  	{
    	c_button = 1;
  	}
	return(c_button);	// Return 0 when z Button pressed
}
int nunchuk_joyX()	
{
	int joy_x_axis=0;
	nunchuk_getData();
	joy_x_axis = __outbuf[0];
	return(joy_x_axis);	// Return 0 when z Button pressed
}
int nunchuk_joyY()	
{
	int joy_y_axis=0;
	nunchuk_getData();
	joy_y_axis = __outbuf[1];
	return(joy_y_axis);	// Return 0 when z Button pressed
}
int nunchuk_ax()	
{
	int accel_x_axis = __outbuf[2] * 2 * 2; 
	nunchuk_getData();
	if ((__outbuf[5] >> 2) & 1)
  	{
    	accel_x_axis += 2;
  	}
  	if ((__outbuf[5] >> 3) & 1)
  	{
    	accel_x_axis += 1;
  	}
	return(accel_x_axis);	// Return 0 when z Button pressed
}
int nunchuk_ay()	
{
	int accel_y_axis = __outbuf[3] * 2 * 2;
	nunchuk_getData();
	if ((__outbuf[5] >> 4) & 1)
  	{
    	accel_y_axis += 2;
  	}
  	if ((__outbuf[5] >> 5) & 1)
  	{
    	accel_y_axis += 1;
  	}
	return(accel_y_axis);	// Return 0 when z Button pressed
}
int nunchuk_az()	
{
	int accel_z_axis = __outbuf[4] * 2 * 2;
	nunchuk_getData();
 	if ((__outbuf[5] >> 6) & 1)
  	{
    	accel_z_axis += 2;
  	}
  	if ((__outbuf[5] >> 7) & 1)
  	{
    	accel_z_axis += 1;
  	}
	return(accel_z_axis);	// Return 0 when z Button pressed
}
#endif

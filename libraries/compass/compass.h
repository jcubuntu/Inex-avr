// HMC6352 compass sensor library
#ifndef _COMPASS_H_
#define _COMPASS_H_
//#include "WProgram.h"
#include "Arduino.h"
#include <./../compass/compass_i2c.h>
#include <math.h>
#include <inttypes.h>
#include <avr/eeprom.h>

#define HMC6352 0x42 //I2C Addr.
#define HMC5883 0x3C //I2C Addr.
#define HMC5983 0x3C //I2C Addr.

#define EEPROM_startAddr 0 // for HMC5883/5983

signed int minMagX=-350; // default value , not calibrated
signed int maxMagX=350;
signed int minMagY=-350;
signed int maxMagY=350;

signed int centerMagX;
signed int centerMagY;

signed int tmpMagX;
signed int tmpMagY;

float readX,readY,dirRad,dirDeg;
int autoAdjustCompassMag=0;
int initCompassPassed=0;
int MagX,MagY,MagZ; //triple axis data

int compassType=HMC5983;

char __compass_ini=0,__compass_heading_ini=0;
int __heading=0;

void compass_readConfig();


void compass_disableAutoTuning(void)
{
  autoAdjustCompassMag=0;
}

void compass_enableAutoTuning(void)
{
  autoAdjustCompassMag=1;
}

void compass_init()
{
  if(__compass_ini==0)
  {
    __compass_ini=1;
	TWBR = 60;	// Ensure decrease bit rate i2c bus                    
    if ((compassType==HMC5883)||(compassType==HMC5983))
    {
      i2c_start();		// Start condition
      i2c_write(compassType);
      i2c_write(0x02);	// Mode register
      i2c_write(0x00); 	//continuous measurement mode
      i2c_stop();	
      i2c_start();		// Start condition
      i2c_write(compassType);
      i2c_write(0x00);	// Addr.0
      i2c_write(0b01111000);	// Reg.A
      i2c_write(0x00);	// Reg.B Gain 0
      i2c_stop();	
      delay(1);
	  compass_readConfig(); // Restore config
    }
  }     
}

int compass_rawX()
{
  compass_init();
  if ((compassType==HMC5883)||(compassType==HMC5983))
  {// HMC5883,5983
    i2c_start();		// Start condition
    i2c_write(compassType);
    i2c_write(0x03);	// Addr.3
    i2c_stop();	
//    delay(1);
    i2c_start();	// Restart condition
    i2c_write(compassType+1);	// Read mode	
    MagX = i2c_read(ACK);	// Read high byte X
    MagX <<=8;				// Shift bit for high byte X
    MagX |= i2c_read(ACK); // Read low byte X
    MagZ = i2c_read(ACK);	// Read high byte Z
    MagZ <<=8;				// Shift bit for high byte Z
    MagZ |= i2c_read(ACK); // Read low byte Z
    MagY = i2c_read(ACK);	// Read high byte Y
    MagY <<=8;				// Shift bit for high byte Y
    MagY |= i2c_read(NACK); // Read low byte Y
    i2c_stop();					// Stop condition
    return int(MagX);
  }
  else
    return 0;

}

int compass_rawY()
{
  compass_init();
  if ((compassType==HMC5883)||(compassType==HMC5983))
  {// HMC5883,5983
    i2c_start();		// Start condition
    i2c_write(compassType);
    i2c_write(0x03);	// Addr.3
    i2c_stop();	
//    delay(1);
    i2c_start();	// Restart condition
    i2c_write(compassType+1);	// Read mode	
    MagX = i2c_read(ACK);	// Read high byte X
    MagX <<=8;				// Shift bit for high byte X
    MagX |= i2c_read(ACK); // Read low byte X
    MagZ = i2c_read(ACK);	// Read high byte Z
    MagZ <<=8;				// Shift bit for high byte Z
    MagZ |= i2c_read(ACK); // Read low byte Z
    MagY = i2c_read(ACK);	// Read high byte Y
    MagY <<=8;				// Shift bit for high byte Y
    MagY |= i2c_read(NACK); // Read low byte Y
    i2c_stop();					// Stop condition
    return int(MagY);
  }
  else
    return 0;

}

int compass_rawZ()
{
  compass_init();
  if ((compassType==HMC5883)||(compassType==HMC5983))
  {// HMC5883,5983
    i2c_start();		// Start condition
    i2c_write(compassType);
    i2c_write(0x03);	// Addr.3
    i2c_stop();	
//    delay(1);
    i2c_start();	// Restart condition
    i2c_write(compassType+1);	// Read mode	
    MagX = i2c_read(ACK);	// Read high byte X
    MagX <<=8;				// Shift bit for high byte X
    MagX |= i2c_read(ACK); // Read low byte X
    MagZ = i2c_read(ACK);	// Read high byte Z
    MagZ <<=8;				// Shift bit for high byte Z
    MagZ |= i2c_read(ACK); // Read low byte Z
    MagY = i2c_read(ACK);	// Read high byte Y
    MagY <<=8;				// Shift bit for high byte Y
    MagY |= i2c_read(NACK); // Read low byte Y
    i2c_stop();					// Stop condition
    return int(MagZ);
  }
  else
    return 0;
}

int compass_read()
{
  unsigned int dat;
  compass_init();
  if (compassType==HMC6352)
  {
    i2c_start();		// Start condition
    i2c_write(compassType);	// Send MCP23016 ID 
    i2c_write('A');	// Send MCP23016 ID 
    i2c_stop();	
    delay(10);
    i2c_start();	// Restart condition
    i2c_write(compassType+1);	// Send CMPS03 ID for Read mode	
    dat = i2c_read(ACK);	// Read high byte from CMPS03(wait acknowledge)
    dat <<=8;				// Shift bit for high byte
    dat |= i2c_read(NACK); // Read low byte from CMPS03(none acknowledge)
    i2c_stop();					// Stop condition
    return(dat/10);		// Return value div 10
  }
  else
  {// HMC5883,5983
    i2c_start();		// Start condition
    i2c_write(compassType);
    i2c_write(0x03);	// Addr.3
    i2c_stop();	
//    delay(1);
    i2c_start();	// Restart condition
    i2c_write(compassType+1);	// Read mode	
    MagX = i2c_read(ACK);	// Read high byte X
    MagX <<=8;				// Shift bit for high byte X
    MagX |= i2c_read(ACK); // Read low byte X
    MagZ = i2c_read(ACK);	// Read high byte Z
    MagZ <<=8;				// Shift bit for high byte Z
    MagZ |= i2c_read(ACK); // Read low byte Z
    MagY = i2c_read(ACK);	// Read high byte Y
    MagY <<=8;				// Shift bit for high byte Y
    MagY |= i2c_read(NACK); // Read low byte Y
    i2c_stop();					// Stop condition

    tmpMagX=MagX;
    tmpMagY=MagY;

    if (autoAdjustCompassMag)
	  if (tmpMagX<minMagX)
        minMagX=tmpMagX;
    if (autoAdjustCompassMag)
      if (tmpMagX>maxMagX)
        maxMagX=tmpMagX;
    if (autoAdjustCompassMag)
      if (tmpMagY<minMagY)
        minMagY=tmpMagY;
    if (autoAdjustCompassMag)
      if (tmpMagY>maxMagY)
        maxMagY=tmpMagY;

    centerMagX=(maxMagX+minMagX)/2;
    centerMagY=(maxMagY+minMagY)/2;

    tmpMagX-=centerMagX;
    tmpMagY-=centerMagY;

    dirRad=atan2(float(tmpMagY),float(tmpMagX));
    dirDeg=(dirRad*180)/PI;
	if (dirDeg==180)
	  dirDeg=179;
    return int(dirDeg+180);
  }
}

void compass_set_heading()
{
  __heading = compass_read();
  if(__compass_heading_ini==0)
  {
    __compass_heading_ini= 1;                     
  }
}

int compass_read_heading()
{
  int ang_new=0,a=0,dir_pos;
  a = compass_read();
  // Positive direction
  dir_pos = __heading+180;
  if(__heading>=180 && __heading<=359)
  {
    if(dir_pos<359)
    {
      ang_new = a-__heading;                                
    }
    else
    {
      if(a>=0 && a<=(dir_pos-360))
      {
        ang_new = (360-__heading)+a;
      }
      else
      {
        ang_new = a-__heading;
        //lcd("#n %d   ",a);
      }         
    }
  }
  else
  {
    ang_new = a-__heading;
    if(a>=0 && a<=__heading)
    {
      ang_new = a-__heading;
    }
    else if(a>=(__heading+180) && a<=359)
    {
      ang_new = (-1)*(__heading+(360-a)); 
    }
  }

  return(ang_new);
}

void compass_writeConfig()
{
  eeprom_write_byte((unsigned char *)EEPROM_startAddr ,(minMagX>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+1,(minMagX%0xff));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+2,(maxMagX>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+3,(maxMagX%0xff));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+4,(minMagY>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+5,(minMagY%0xff));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+6,(maxMagY>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+7,(maxMagY%0xff));
}

void compass_writeConfig(int minMagX1,int maxMagX1,int minMagY1,int maxMagY1)
{
  eeprom_write_byte((unsigned char *)EEPROM_startAddr ,(minMagX1>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+1,(minMagX1%0xff));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+2,(maxMagX1>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+3,(maxMagX1%0xff));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+4,(minMagY1>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+5,(minMagY1%0xff));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+6,(maxMagY1>>8));
  eeprom_write_byte((unsigned char *)EEPROM_startAddr+7,(maxMagY1%0xff));
}

void compass_readConfig()
{
  minMagX=(eeprom_read_byte((unsigned char *)EEPROM_startAddr))<<8;
  minMagX+=eeprom_read_byte((unsigned char *)EEPROM_startAddr+1);
  maxMagX=(eeprom_read_byte((unsigned char *)EEPROM_startAddr+2))<<8;
  maxMagX+=eeprom_read_byte((unsigned char *)EEPROM_startAddr+3);
  minMagY=(eeprom_read_byte((unsigned char *)EEPROM_startAddr+4))<<8;
  minMagY+=eeprom_read_byte((unsigned char *)EEPROM_startAddr+5);
  maxMagY=(eeprom_read_byte((unsigned char *)EEPROM_startAddr+6))<<8;
  maxMagY+=eeprom_read_byte((unsigned char *)EEPROM_startAddr+7);
}

void compass_scan(int scanTime)
{
  unsigned long scanTimer;
  int tmpautoAdjustCompassMag;
  tmpautoAdjustCompassMag=autoAdjustCompassMag;
  scanTimer=millis()+scanTime;
  autoAdjustCompassMag=1;
  while(millis()<scanTimer)
  {	
    compass_read();
  }
  autoAdjustCompassMag=tmpautoAdjustCompassMag;
  compass_writeConfig();
}

void compass_factoryReset(void)
{
  minMagX=-350; // default value , not calibrated
  maxMagX=350;
  minMagY=-350;
  maxMagY=350;
  compass_writeConfig();
}

#endif
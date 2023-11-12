//
// Compass calibration 
//

//#include <compass.h> // for other standard board
//#include <ATX2.h> // for ATX2 Board (already inc. compass.h)
#include <popx2.h> // for POP-X2 Board (already inc. compass.h)

int minX=0;  
int minY=0;
int maxX=0;
int maxY=0;

void setup()
{
  OK();
  compass_read(); // initialize read at First times
}

void loop()
{
  int readValue;
  compass_factoryReset(); // preset default value
  compass_enableAutoTuning(); // Enable auto tuning
  while(1)
  {
    readValue=compass_read();
	// raw data reading MagX MagY variable on library
	// compare & replace lower/upper limit
    if (MagX<minX)
      minX=MagX;
    if (MagX>maxX)
      maxX=MagX;
    if (MagY<minY)
      minY=MagY;
    if (MagY>maxY)
      maxY=MagY;

    glcd(0,0,"X:%d   ",MagX);
    glcd(1,0,"%d   ",minX);
    glcd(1,7,"%d   ",maxX);
    glcd(2,0,"Y:%d   ",MagY);
    glcd(3,0,"%d   ",minY);
    glcd(3,7,"%d   ",maxY);
    glcd(4,0,"Deg:%d  ",readValue,DEC);
	// push switch OK to record value on EEPROM (POP-X2 or other boards which EESAVE fuse was set)
	//if (sw_OK())
	//	compass_writeConfig(minX,maxX,minY,maxY);
	//

  }
}



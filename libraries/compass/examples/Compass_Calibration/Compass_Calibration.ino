//
// Compass calibration 
//

#include <compass.h> // for other standard board
//#include <ATX2.h> // for ATX2 Board (already inc. compass.h)
//#include <popx2.h> // for POP-X2 Board (already inc. compass.h)

int minX=0;  
int minY=0;
int maxX=0;
int maxY=0;

void setup()
{
  while(!Serial);  // Wait for terminal opened

  Serial.begin(9600);
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

    Serial.print("X:"); 
    Serial.print(MagX,DEC);
    Serial.print(" minX:"); 
    Serial.print(minX,DEC);
    Serial.print(" maxX:"); 
    Serial.print(maxX,DEC);
    Serial.print(" Y:"); 
    Serial.print(MagY,DEC);
    Serial.print(" minY:"); 
    Serial.print(minY,DEC);
    Serial.print(" maxY:"); 
    Serial.print(maxY,DEC);
    Serial.print(" Degree:"); 
    Serial.print(readValue,DEC);
    Serial.println();
    delay(100);

	// push switch OK to record value on EEPROM (POP-X2 or other boards which EESAVE fuse was set)
	//if (sw_OK())
	//	compass_writeConfig(minX,maxX,minY,maxY);
	//
  }
}



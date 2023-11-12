//
// Compass read test
// (after calibration already)
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
  compass_set_heading(); // Set heading to 0
}

void loop()
{
  int readValue;
  int readHeadValue;
  while(1)
  {
    readValue=compass_read();	// read Absolute direction
    readHeadValue=compass_read_heading(); // read heading direction
    Serial.print("Real:");
    Serial.print(readValue,DEC);
    Serial.print("  Head:");
    Serial.println(readHeadValue,DEC);
    delay(100);
  }
}



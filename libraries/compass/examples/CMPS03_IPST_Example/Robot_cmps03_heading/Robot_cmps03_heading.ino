#include <ipst.h>
#define RANGE 10
void setup()
{
  OK();
  cmps03_set_heading();  // Set heading at first time(compass sensor) 
}
void loop()
{
  int angle = cmps03_read_heading();  // Read heading
  if(angle>=-RANGE && angle<=RANGE)  // Robot read angle between +/- 2 degree?
  {
    fd(40);  // Robot forward
  }
  else if(angle<-RANGE)  // Robot over to left side?
  {
    sr(40);  // Robot spin right
  }
  else if(angle>RANGE)  // Robot over to right side?
  {
    sl(40);  // Robot spin left
  }
}

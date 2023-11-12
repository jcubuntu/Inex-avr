#include <ipst.h>
#define RANGE 10
void setup()
{
  OK();
  cmps03_pwm_set_heading(2);  // Set heading at first time(compass sensor) 
}
void loop()
{
  int angle = cmps03_pwm_read_heading();  // Read heading
  if(angle>=-RANGE && angle<=RANGE)  // Robot read angle between +/- 2 degree?
  {
    fd(25);  // Robot forward
  }
  else if(angle<-RANGE)  // Robot over to left side?
  {
    sr(25);  // Robot spin right
  }
  else if(angle>RANGE)  // Robot over to right side?
  {
    sl(25);  // Robot spin left
  }
}

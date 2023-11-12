#include <ipst.h>	// IPST-SE Board
void setup() 
{
  glcdClear();
  glcdMode(3);
  cmps03_pwm_set_heading(2);
}
void loop() 
{
  glcd(0,0,"CMPS03 = %d    ",cmps03_pwm_read_heading());
}

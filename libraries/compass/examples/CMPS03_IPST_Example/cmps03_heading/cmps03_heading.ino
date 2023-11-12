#include <ipst.h>	// IPST-SE Board
void setup() 
{
  glcdClear();
  glcdMode(3);
  cmps03_set_heading();
}
void loop() 
{
  glcd(0,0,"CMPS03 = %d    ",cmps03_read_heading());
}

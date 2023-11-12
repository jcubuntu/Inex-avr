#include <ipst.h>	// IPST-SE Board
void setup() 
{
  glcdMode(3);
}
void loop() 
{
  glcd(0,0,"CMPS03 = %d    ",cmps03_read());
}

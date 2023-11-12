#include <popx2.h> // Include Library for POP-X2 Board 
void setup()
{
  glcdMode(3);  // Set GLCD Mode
  cmps11_mode(MODE_SERIAL);  // Used connetion mode serial
}
void loop()
{
  glcd(0,0,"CMPS11 = %d   ",cmps11_read());  // Read angle and display 
}

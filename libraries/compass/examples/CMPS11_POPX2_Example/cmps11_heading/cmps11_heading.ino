#include <popx2.h> // Include Library for POP-X2 Board 
void setup()
{
  glcdClear();  // Clear GLCD
  glcdMode(3);  // Set GLCD Mode
  cmps11_set_heading();
}
void loop()
{
  glcd(0,0,"head = %d   ",cmps11_read_heading());  // Read angle and display 
}

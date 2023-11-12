#include <popx2.h>
void setup()
{
  glcdMode(3);
}
void loop()
{
  glcd(0,0,"CMPS11 Read");
  glcd(2,0,"Pitch: %d   ",cmps11_read_pitch()); 
  glcd(3,0,"Roll: %d   ",cmps11_read_roll()); 
}

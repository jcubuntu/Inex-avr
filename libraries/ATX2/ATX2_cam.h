
#ifndef _ATX2_CMUCAM_H_
#define _ATX2_CMUCAM_H_

#include <avr/io.h>
#include <ATX2_serial.h>
#include <ATX2_sleep.h>

#define MID_X 40  // Center X ==> 80/2
#define MID_Y 71  // Center Y ==> 143/2


unsigned char __conf=0;
unsigned char __mx=0;  // width 80
unsigned char __my=0;  // width 143

void cam_RS()
{
  uart1("RS\r"); // Send command for Reset CMUcam
}
void cam_MM(char _mode)
{
  uart1("MM %d\r",_mode);        // Middle mas mode
}
void cam_RM(char _mode)
{
  uart1("RM %d\r",_mode);        // Raw serial transfer mode
}
void cam_PM(char _mode)
{
  uart1("PM %d\r",_mode);        // Polling mode 
}

void cam_TW(long _ms)
{

  uart1("TW\r"); // Send command for Track window
  sleep(_ms);
}
void cam_L1(char cmd)
{
  switch(cmd)
  {
  case 0: 
    uart1("l1 0\r");   // Send command for L1 OFF
    break;
  case 1: 
    uart1("l1 1\r");   // Send command for L1 ON
    break;
  case 2: 
    uart1("l1 2\r");   // Send command for L1 AUTOMATIC
    break;
  default: 
    break;
  }
}
void cam_TC_ref(unsigned char _rmin,unsigned char _rmax,unsigned char _gmin,unsigned char _gmax,unsigned char _bmin,unsigned char _bmax)
{
  // Send command for Track color reference by value   
  uart1("TC %d %d %d %d %d %d\r",_rmin,_rmax,_gmin,_gmax,_bmin,_bmax); 
}
void cam_TC()
{
  uart1("TC\r"); // Send command for Track color after Track window 
}
void cam_GM()
{
  uart1("GM\r"); // Send command for get mean object 
}
unsigned char * cam_get_mean()
{
  int i;
  static unsigned char dat[6];
  //cam_TW(300);       // Track window 
  cam_GM();   // Get Mean 
  while(1)
  {
    if(uart1_available())
    {
      if(uart1_getkey()=='S')
      {
        for(i=0;i<6;i++)
        {  
          while(!uart1_available());
          dat[i] = uart1_getkey();
        }
        break; 
      }
    }  
  }
  return(&dat[0]);
}
unsigned char * cam_track_color(unsigned char rmin,unsigned char rmax,unsigned char gmin,unsigned char gmax,unsigned char bmin,unsigned char bmax)
{
  int i;
  static unsigned char dat[8];
  //cam_TW(300);       // Track window 
  cam_TC_ref(rmin,rmax,gmin,gmax,bmin,bmax);   // Track Color by reference value(mean +/-30 or +-20)
  while(1)
  {
    if(uart1_available())
    {
      if(uart1_getkey()=='M')
      {
        for(i=0;i<8;i++)
        {  
          while(!uart1_available());
          dat[i] = uart1_getkey();
        }
        break; 
      }
    }  
  }
  return(&dat[0]);
}
void cam_init()
{
  uart1_set_baud(9600);           
  cam_RS();     // Reset Cam       
  sleep(100);
  uart1_flush();
  cam_RM(1);    // Raw serial transfer mode
  sleep(100);
  uart1_flush();
  cam_PM(1);    // Polling mode enable
  sleep(100);
  uart1_flush();
  cam_L1(2);    // Light tracking auto
  sleep(100);
  uart1_flush();
}
#endif


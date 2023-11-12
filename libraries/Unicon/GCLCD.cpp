// Graphics library by ladyada/adafruit with init code from Rossum 
// MIT license

#include "GCLCD.h"
#include "glcdfont.c"
#include <avr/pgmspace.h>
#include "pins_arduino.h"
#include "wiring_private.h"
#include <UniconSPI.h>

// chipmode 0 = initB initR
// chipmode 1 = initIL
static unsigned char GCLCD_chipmode=0;
static unsigned char GCLCD_screenAlignment=0;
static unsigned char GCLCD_BGR=1; // POP-XT=0 POP-XT+=1
GCLCD::GCLCD(uint8_t cs, uint8_t rs, uint8_t sid, uint8_t sclk) {
  _cs = cs;
  _rs = rs;
  _sid = sid;
  _sclk = sclk;
}

GCLCD::GCLCD(uint8_t cs, uint8_t rs) {
  _cs = cs;
  _rs = rs;
  _sid = 0;
  _sclk = 0;
}



inline void GCLCD::spiwrite(uint8_t c) {

  //Serial.println(c, HEX);

  if (!_sid) {
    UniconSPI.transfer(c);
    return;
  }

  volatile uint8_t *sclkportreg = portOutputRegister(sclkport);
  volatile uint8_t *sidportreg = portOutputRegister(sidport);

  int8_t i;

  *sclkportreg |= sclkpin;

  for (i=7; i>=0; i--) {
    *sclkportreg &= ~sclkpin;
    //SCLK_PORT &= ~_BV(SCLK);
    
    if (c & _BV(i)) {
      *sidportreg |= sidpin;
      //digitalWrite(_sid, HIGH);
      //SID_PORT |= _BV(SID);
    } else {
      *sidportreg &= ~sidpin;
      //digitalWrite(_sid, LOW);
      //SID_PORT &= ~_BV(SID);
    }
    
    *sclkportreg |= sclkpin;
    //SCLK_PORT |= _BV(SCLK);
  }
}




void GCLCD::writecommand(uint8_t c) {
  *portOutputRegister(rsport) &= ~ rspin;
  //digitalWrite(_rs, LOW);

  *portOutputRegister(csport) &= ~ cspin;
  //digitalWrite(_cs, LOW);

  //Serial.print("C ");
  spiwrite(c);

  *portOutputRegister(csport) |= cspin;
  //digitalWrite(_cs, HIGH);
}


void GCLCD::writedata(uint8_t c) {
  *portOutputRegister(rsport) |= rspin;
  //digitalWrite(_rs, HIGH);

  *portOutputRegister(csport) &= ~ cspin;
    //digitalWrite(_cs, LOW);

  //Serial.print("D ");
  spiwrite(c);

  *portOutputRegister(csport) |= cspin;
  //digitalWrite(_cs, HIGH);
} 


void GCLCD::setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  writecommand(GCLCD_CASET);  // column addr set
  writedata(0x00);
  if ((GCLCD_chipmode==0)&&(GCLCD_screenAlignment==0))
	writedata(x0+2);   // XSTART 
  else
	writedata(x0);   // XSTART 

  writedata(0x00);
  if ((GCLCD_chipmode==0)&&(GCLCD_screenAlignment==0))
	writedata(x1+2);   // XEND
  else
	writedata(x1);   // XEND

  writecommand(GCLCD_RASET);  // row addr set
  writedata(0x00);
  if ((GCLCD_chipmode==0)&&(GCLCD_screenAlignment==0))
	writedata(y0+1);    // YSTART
  else
	writedata(y0);    // YSTART

  writedata(0x00);
  if ((GCLCD_chipmode==0)&&(GCLCD_screenAlignment==0))
	writedata(y1+1);    // YEND
  else
	writedata(y1);    // YEND

  writecommand(GCLCD_RAMWR);  // write to RAM
}

void GCLCD::pushColor(uint16_t color) {
  *portOutputRegister(rsport) |= rspin;
  *portOutputRegister(csport) &= ~ cspin;

  spiwrite(color >> 8);    
  spiwrite(color);   

  *portOutputRegister(csport) |= cspin;
}

void GCLCD::drawPixel(uint8_t x, uint8_t y,uint16_t color) {
  if ((x >= width) || (y >= height)) return;

  setAddrWindow(x,y,x+1,y+1);

  // setup for data
  *portOutputRegister(rsport) |= rspin;
  *portOutputRegister(csport) &= ~ cspin;

  spiwrite(color >> 8);    
  spiwrite(color);   

  *portOutputRegister(csport) |= cspin;

}


void GCLCD::fillScreen(uint16_t color) {
  setAddrWindow(0, 0, width-1, height-1);

  // setup for data
  *portOutputRegister(rsport) |= rspin;
  *portOutputRegister(csport) &= ~ cspin;

  for (uint8_t x=0; x < width; x++) {
    for (uint8_t y=0; y < height; y++) {
      spiwrite(color >> 8);    
      spiwrite(color);    
    }
  }

  *portOutputRegister(csport) |= cspin;
}

void GCLCD::initB(void) {
  // set pin directions
  GCLCD_chipmode=0;
  pinMode(_rs, OUTPUT);
  width=128;
  height=160;

  if (_sclk) {
    pinMode(_sclk, OUTPUT);
    sclkport = digitalPinToPort(_sclk);
    sclkpin = digitalPinToBitMask(_sclk);

    pinMode(_sid, OUTPUT);
    sidport = digitalPinToPort(_sid);
    sidpin = digitalPinToBitMask(_sid);
  } else {
    // using the hardware SPI
    UniconSPI.begin();
    UniconSPI.setDataMode(SPI_MODE3);
  }
  // toggle RST low to reset; CS low so it'll listen to us
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, LOW);
  cspin = digitalPinToBitMask(_cs);
  csport = digitalPinToPort(_cs);

  rspin = digitalPinToBitMask(_rs);
  rsport = digitalPinToPort(_rs);

/*
  if (_rst) {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH);
    delay(500);
    digitalWrite(_rst, LOW);
    delay(500);
    digitalWrite(_rst, HIGH);
    delay(500);
  }
*/
  writecommand(GCLCD_SWRESET); // software reset
  delay(50);
  writecommand(GCLCD_SLPOUT);  // out of sleep mode
  delay(500);
  
  writecommand(GCLCD_COLMOD);  // set color mode
  writedata(0x05);        // 16-bit color
  delay(10);
  
  writecommand(GCLCD_FRMCTR1);  // frame rate control
  writedata(0x00);  // fastest refresh
  writedata(0x06);  // 6 lines front porch
  writedata(0x03);  // 3 lines backporch
  delay(10);
  
  writecommand(GCLCD_MADCTL);  // memory access control (directions)
  writedata(0x08);  // row address/col address, bottom to top refresh
  madctl = 0x08;

  writecommand(GCLCD_DISSET5);  // display settings #5
  writedata(0x15);  // 1 clock cycle nonoverlap, 2 cycle gate rise, 3 cycle oscil. equalize
  writedata(0x02);  // fix on VTL
 
  writecommand(GCLCD_INVCTR);  // display inversion control
  writedata(0x0);  // line inversion
 
  writecommand(GCLCD_PWCTR1);  // power control
  writedata(0x02);      // GVDD = 4.7V 
  writedata(0x70);      // 1.0uA
  delay(10);
  writecommand(GCLCD_PWCTR2);  // power control
  writedata(0x05);      // VGH = 14.7V, VGL = -7.35V 
  writecommand(GCLCD_PWCTR3);  // power control
  writedata(0x01);      // Opamp current small 
  writedata(0x02);      // Boost frequency
  
  
  writecommand(GCLCD_VMCTR1);  // power control
  writedata(0x3C);      // VCOMH = 4V
  writedata(0x38);      // VCOML = -1.1V
  delay(10);
  
  writecommand(GCLCD_PWCTR6);  // power control
  writedata(0x11); 
  writedata(0x15);
  
  writecommand(GCLCD_GMCTRP1);
  writedata(0x09);
  writedata(0x16);
  writedata(0x09);
  writedata(0x20);
  writedata(0x21);
  writedata(0x1B);
  writedata(0x13);
  writedata(0x19);
  writedata(0x17);
  writedata(0x15);
  writedata(0x1E);
  writedata(0x2B);
  writedata(0x04);
  writedata(0x05);
  writedata(0x02);
  writedata(0x0E);
  writecommand(GCLCD_GMCTRN1);
  writedata(0x0B); 
  writedata(0x14); 
  writedata(0x08); 
  writedata(0x1E); 
  writedata(0x22); 
  writedata(0x1D); 
  writedata(0x18); 
  writedata(0x1E); 
  writedata(0x1B); 
  writedata(0x1A); 
  writedata(0x24); 
  writedata(0x2B); 
  writedata(0x06); 
  writedata(0x06); 
  writedata(0x02); 
  writedata(0x0F); 
  delay(10);
  
  writecommand(GCLCD_CASET);  // column addr set
  writedata(0x00);
  writedata(0x02);   // XSTART = 2
  writedata(0x00);
  writedata(0x81);   // XEND = 129

  writecommand(GCLCD_RASET);  // row addr set
  writedata(0x00);
  writedata(0x02);    // XSTART = 1
  writedata(0x00);
  writedata(0x81);    // XEND = 160

  writecommand(GCLCD_NORON);  // normal display on
  delay(10);
  
  writecommand(GCLCD_DISPON);
  delay(500);
}


void GCLCD::initR(void) {
  GCLCD_screenAlignment=0;
  initST();
}

void GCLCD::initS(void) {
  GCLCD_screenAlignment=1;
  GCLCD_BGR=1;
  initST();
}

void GCLCD::initSBGR(void) {
  GCLCD_screenAlignment=1;
  GCLCD_BGR=1;
  initST();
}

void GCLCD::initST(void) {
  // set pin directions
  GCLCD_chipmode=0;
  pinMode(_rs, OUTPUT);
  width=128;
  height=160;

  if (_sclk) {
    pinMode(_sclk, OUTPUT);
    sclkport = digitalPinToPort(_sclk);
    sclkpin = digitalPinToBitMask(_sclk);

    pinMode(_sid, OUTPUT);
    sidport = digitalPinToPort(_sid);
    sidpin = digitalPinToBitMask(_sid);
  } else {
    // using the hardware SPI
    UniconSPI.begin();
    UniconSPI.setDataMode(SPI_MODE3);
  }
  // toggle RST low to reset; CS low so it'll listen to us
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, LOW);
  cspin = digitalPinToBitMask(_cs);
  csport = digitalPinToPort(_cs);

  rspin = digitalPinToBitMask(_rs);
  rsport = digitalPinToPort(_rs);

/*
  if (_rst) {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH);
    delay(500);
    digitalWrite(_rst, LOW);
    delay(500);
    digitalWrite(_rst, HIGH);
    delay(500);
  }
*/

  writecommand(GCLCD_SWRESET); // software reset
  delay(150);

  writecommand(GCLCD_SLPOUT);  // out of sleep mode
  delay(500);

  writecommand(GCLCD_FRMCTR1);  // frame rate control - normal mode
  writedata(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
  writedata(0x2C); 
  writedata(0x2D); 

  writecommand(GCLCD_FRMCTR2);  // frame rate control - idle mode
  writedata(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
  writedata(0x2C); 
  writedata(0x2D); 

  writecommand(GCLCD_FRMCTR3);  // frame rate control - partial mode
  writedata(0x01); // dot inversion mode
  writedata(0x2C); 
  writedata(0x2D); 
  writedata(0x01); // line inversion mode
  writedata(0x2C); 
  writedata(0x2D); 
  
  writecommand(GCLCD_INVCTR);  // display inversion control
  writedata(0x07);  // no inversion

  writecommand(GCLCD_PWCTR1);  // power control
  writedata(0xA2);      
  writedata(0x02);      // -4.6V
  writedata(0x84);      // AUTO mode

  writecommand(GCLCD_PWCTR2);  // power control
  writedata(0xC5);      // VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD

  writecommand(GCLCD_PWCTR3);  // power control
  writedata(0x0A);      // Opamp current small 
  writedata(0x00);      // Boost frequency

  writecommand(GCLCD_PWCTR4);  // power control
  writedata(0x8A);      // BCLK/2, Opamp current small & Medium low
  writedata(0x2A);     

  writecommand(GCLCD_PWCTR5);  // power control
  writedata(0x8A);    
  writedata(0xEE);     

  writecommand(GCLCD_VMCTR1);  // power control
  writedata(0x0E);  

  writecommand(GCLCD_INVOFF);    // don't invert display

  writecommand(GCLCD_MADCTL);  // memory access control (directions)
  if (GCLCD_BGR==0)
  {
    writedata(0xc8);  // row address/col address, bottom to top refresh
    madctl = 0xc8;
  }
  else
  {
    writedata(0xc0);  // row address/col address, bottom to top refresh
    madctl = 0xc0;
  }
  
  writecommand(GCLCD_COLMOD);  // set color mode
  writedata(0x05);        // 16-bit color

  writecommand(GCLCD_CASET);  // column addr set
  writedata(0x00);
  writedata(0x00);   // XSTART = 0
  writedata(0x00);
  writedata(0x7F);   // XEND = 127

  writecommand(GCLCD_RASET);  // row addr set
  writedata(0x00);
  writedata(0x00);    // XSTART = 0
  writedata(0x00);
  writedata(0x9F);    // XEND = 159

  writecommand(GCLCD_GMCTRP1);
  writedata(0x02);
  writedata(0x1c);
  writedata(0x07);
  writedata(0x12);
  writedata(0x37);
  writedata(0x32);
  writedata(0x29);
  writedata(0x2d);
  writedata(0x29);
  writedata(0x25);
  writedata(0x2B);
  writedata(0x39);
  writedata(0x00);
  writedata(0x01);
  writedata(0x03);
  writedata(0x10);
  writecommand(GCLCD_GMCTRN1);
  writedata(0x03); 
  writedata(0x1d); 
  writedata(0x07); 
  writedata(0x06); 
  writedata(0x2E); 
  writedata(0x2C); 
  writedata(0x29); 
  writedata(0x2D); 
  writedata(0x2E); 
  writedata(0x2E); 
  writedata(0x37); 
  writedata(0x3F); 
  writedata(0x00); 
  writedata(0x00); 
  writedata(0x02); 
  writedata(0x10); 
  
  writecommand(GCLCD_DISPON);
  delay(100);

  writecommand(GCLCD_NORON);  // normal display on
  delay(10);
}

void GCLCD::initIL(void) {
  width=128;
  height=160;

	// set pin directions
  GCLCD_chipmode=1; // mode IL
  pinMode(_rs, OUTPUT);

  if (_sclk) {
    pinMode(_sclk, OUTPUT);
    sclkport = digitalPinToPort(_sclk);
    sclkpin = digitalPinToBitMask(_sclk);

    pinMode(_sid, OUTPUT);
    sidport = digitalPinToPort(_sid);
    sidpin = digitalPinToBitMask(_sid);
  } else {
    // using the hardware SPI
    UniconSPI.begin();
    UniconSPI.setDataMode(SPI_MODE3);
  }
  // toggle RST low to reset; CS low so it'll listen to us
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, LOW);
  cspin = digitalPinToBitMask(_cs);
  csport = digitalPinToPort(_cs);

  rspin = digitalPinToBitMask(_rs);
  rsport = digitalPinToPort(_rs);

/*
  if (_rst) {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH);
    delay(500);
    digitalWrite(_rst, LOW);
    delay(500);
    digitalWrite(_rst, HIGH);
    delay(500);
  }
*/

    writecommand(0x11);       //start OSC
    delay(100);
    
    writecommand(0x3a);       //interface pixel format
    writedata(0x05);
   
    writecommand(0x26);       //gamma set
    writedata(0x04);
	
    writecommand(0xf2);              //GAM_R_SEL
    writedata(0x01);
    
    writecommand(0xe0);              //positive gamma correction setting
    writedata(0x3f);
    writedata(0x25);
    writedata(0x1c);
    writedata(0x1e);
    writedata(0x20);
    writedata(0x12);
    writedata(0x2a);
    writedata(0x90);
    writedata(0x24);
    writedata(0x11);
    writedata(0x00);
    writedata(0x00);
    writedata(0x00);
    writedata(0x00);
    writedata(0x00);
     
    writecommand(0xe1);              //negative gamma correction setting
    writedata(0x20);
    writedata(0x20);
    writedata(0x20);
    writedata(0x20);
    writedata(0x05);
    writedata(0x00);
    writedata(0x15);
    writedata(0xa7);
    writedata(0x3d);
    writedata(0x18);
    writedata(0x25);
    writedata(0x2a);
    writedata(0x2b);
    writedata(0x2b);  
    writedata(0x3a);  
    
    writecommand(0xb1);              //frame rate control
    writedata(0x08);
    writedata(0x08);
    
    writecommand(0xb4);              //display inversion control
    writedata(0x07);
   
   
    writecommand(0xc0);              //power control1
    writedata(0x0a);
    writedata(0x02);
      
    writecommand(0xc1);              //power control2
    writedata(0x02);

    writecommand(0xc5);              //power control5
    writedata(0x4f);
    writedata(0x5a);

    writecommand(0xc7);              //VCOM offset control
    writedata(0x40);
    
    writecommand(0x2a);              //column address set
    writedata(0x00);	// start
    writedata(0x00);
    writedata(0x00);	// end
    writedata(0x7f);	// 7f

    writecommand(0x2b);              //page address set
    writedata(0x00);	// start
    writedata(0x00);
    writedata(0x00);	// end
    writedata(0x9F);	// 9f

	writecommand(0x36);              //memory access control
    writedata(0xc0);
    madctl = 0xc0;

	writecommand(0x37);              //memory access control
    writedata(0x00);
    writedata(0x00);

    writecommand(0xb7);              //source driver direction control
    writedata(0x00);

//    writecommand(0xb8);              //gate driver direction control
//    writedata(0x01);
	   
    writecommand(0x29);   			// display on
    writecommand(0x2c);
}





/*
// draw a string from memory

void GCLCD::drawString(uint8_t x, uint8_t y, char *c, 
			uint16_t color, uint8_t size) {
  while (c[0] != 0) {
    drawChar(x, y, c[0], color, size);
    x += size*6;
    c++;
    if (x + 5 >= width) {
      y += 10;
      x = 0;
    }
  }
}
// draw a character
void GCLCD::drawChar(uint8_t x, uint8_t y, char c, 
		      uint16_t color, uint8_t size) {
  for (uint8_t i =0; i<5; i++ ) {
    uint8_t line = pgm_read_byte(font+(c*5)+i);
    for (uint8_t j = 0; j<8; j++) {
      if (line & 0x1) {
	if (size == 1) // default size
	  drawPixel(x+i, y+j, color);
	else {  // big size
	  fillRect(x+i*size, y+j*size, size, size, color);
	} 
      }
      line >>= 1;
    }
  }
}
*/
// draw a string from memory

void GCLCD::drawString(uint8_t x, uint8_t y, char *c, 
			uint16_t color,uint16_t bgcolor, uint8_t size) {
	x = x*size;
	y = y*size+1;
  while (c[0] != 0) {
    drawChar(x, y, c[0], color,bgcolor, size);
    x += size*6;
    c++;
    if ((x + (size*5)) >= width) {
//      y += 10;
      y += size*10;
      x = 0;
    }
  }
}
// draw a character
void GCLCD::drawChar(uint8_t x, uint8_t y, char c, 
		      uint16_t color, uint16_t bgcolor,uint8_t size) {
  for (uint8_t i =0; i<5; i++ ) {
    uint8_t line = pgm_read_byte(font+(c*5)+i);
    for (uint8_t j = 0; j<8; j++) {
      if (line & 0x1) 
      {
	     if (size == 1) // default size
		 {
	        drawPixel(x+i, y+j, color);
		 }
	     else 
         {  // big size
	        fillRect(x+(i*size), y+(j*size), size, size, color);
	     } 
      }
      else  // Addition test
      {
         if (size == 1) // default size
		{
	      drawPixel(x+i, y+j, bgcolor);
			}
	     else 
         {  // big size
	        fillRect(x+(i*size), y+(j*size), size, size, bgcolor);
	     } 
      }
      line >>= 1;
    }
  }
   for (uint8_t j = 0; j<8; j++)      // draw space vertical line 
   {
         if (size == 1) // default size
		 {
	        drawPixel(x+5, y+j, bgcolor);
		 }
	     else 
         {  // big size
	        fillRect(x+(5*size), y+(j*size), size, size, bgcolor);
	     } 

   }
}


void GCLCD::drawStringTransparent(uint8_t x, uint8_t y, char *c, 
			uint16_t color, uint8_t size) {
	x = x*size;
	y = y*size+1;
  while (c[0] != 0) {
    drawCharTransparent(x, y, c[0], color, size);
    x += size*6;
    c++;
    if ((x + (size*5)) >= width) {
//      y += 10;
      y += size*10;
      x = 0;
    }
  }
}
// draw a character transparent mode
void GCLCD::drawCharTransparent(uint8_t x, uint8_t y, char c, 
		      uint16_t color,uint8_t size) {
  for (uint8_t i =0; i<5; i++ ) {
    uint8_t line = pgm_read_byte(font+(c*5)+i);
    for (uint8_t j = 0; j<8; j++) {
      if (line & 0x1) 
      {
	     if (size == 1) // default size
		 {
	        drawPixel(x+i, y+j, color);
		 }
	     else 
         {  // big size
	        fillRect(x+(i*size), y+(j*size), size, size, color);
	     } 
      }
      line >>= 1;
    }
  }
}

// fill a circle
void GCLCD::fillCircle(uint8_t x0, uint8_t y0, uint8_t r, uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawVerticalLine(x0, y0-r, 2*r+1, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawVerticalLine(x0+x, y0-y, 2*y+1, color);
    drawVerticalLine(x0-x, y0-y, 2*y+1, color);
    drawVerticalLine(x0+y, y0-x, 2*x+1, color);
    drawVerticalLine(x0-y, y0-x, 2*x+1, color);
  }
}

// draw a circle outline
void GCLCD::drawCircle(uint8_t x0, uint8_t y0, uint8_t r, 
			uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0, y0+r, color);
  drawPixel(x0, y0-r, color);
  drawPixel(x0+r, y0, color);
  drawPixel(x0-r, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
    
  }
}

uint16_t __q2Pow(uint16_t radius)
{
  uint16_t __q2PowResult=1;
  uint16_t i; 
  if (radius!=0)
  {
	for (i=0;i<radius;i++)
	{
		__q2PowResult=__q2PowResult<<1;
	}
  }
  return __q2PowResult;
}

uint16_t __qSqrt(uint16_t rSqr)
{
  uint16_t __qSqrtTrialNumber=128;
  uint16_t __qSqrtPowTrialNumber;
  uint8_t __qSqrtTrialCounter=6;
  uint8_t i;
  for (i=0;i<7;i++)
  {
		__qSqrtPowTrialNumber=__qSqrtTrialNumber*__qSqrtTrialNumber;
		if ((__qSqrtPowTrialNumber)==rSqr)
		{
			return __qSqrtTrialNumber;
		}
		else
		{
			if ((__qSqrtPowTrialNumber)>rSqr)
			{
				__qSqrtTrialNumber=__qSqrtTrialNumber-__q2Pow(__qSqrtTrialCounter);
			}
			else
			{
				__qSqrtTrialNumber=__qSqrtTrialNumber+__q2Pow(__qSqrtTrialCounter);
			}
			__qSqrtTrialCounter--;			
		}
  }
  if ((__qSqrtTrialNumber*__qSqrtTrialNumber) > rSqr)
  {
	__qSqrtTrialNumber=__qSqrtTrialNumber-1;
  }
  return __qSqrtTrialNumber;
}

void GCLCD::drawArc(uint8_t h,uint8_t k,uint8_t r,int16_t start_angle,int16_t end_angle,uint16_t color)
{
	  int16_t angle,angleTmp;
	  int16_t x;//,y;
	  float y;
	  angle=start_angle;

      while(angle<=end_angle)
      {
		y=(r*(sin((angle%180)*(M_PI/180))));
		x=(__qSqrt((r*r)-(y*y)));
		angleTmp=angle%360;
		if (angleTmp<90)
		{
		  drawPixel((int)(h+x),(int)(k-y),color);
		}
		else if (angleTmp<180)
		{
		  drawPixel((int)(h-x),(int)(k-y),color);
		}
		else if (angleTmp<270)
		{
		  drawPixel((int)(h-x),(int)(k+y),color);
		}
		else// if (angleTmp<360)
		{
		  drawPixel((int)(h+x),(int)(k+y),color);
		}
		
	
        angle++;
      }
}

/*
void GCLCD::drawPie(uint8_t h,uint8_t k,uint8_t r,int16_t start_angle,int16_t end_angle,uint16_t color)
{
	  int16_t angle,angleTmp;
	  int16_t x;//,y;
	  float y;
	  angle=start_angle;

      while(angle<=end_angle)
      {
		y=(r*(sin((angle%180)*(M_PI/180))));
		x=(__qSqrt((r*r)-(y*y)));
		angleTmp=angle%360;
		if (angleTmp<90)
		{
		  drawLine(h,k,(int)(h+x),(int)(k-y),color);
		}
		else if (angleTmp<180)
		{
		  drawLine(h,k,(int)(h-x),(int)(k-y),color);
		}
		else if (angleTmp<270)
		{
		  drawLine(h,k,(int)(h-x),(int)(k+y),color);
		}
		else// if (angleTmp<360)
		{
		  drawLine(h,k,(int)(h+x),(int)(k+y),color);
		}
        angle++;
      }
}
*/
/*
void GCLCD::drawArc(uint8_t h,uint8_t k,uint8_t r,int16_t start_angle,int16_t end_angle,uint16_t color)
{

       float angle=(((start_angle<=end_angle)?start_angle:end_angle)*(M_PI/180));
       float range=(((end_angle>start_angle)?end_angle:start_angle)*(M_PI/180));

       float x=(r*cos(angle));
       float y=(r*sin(angle));

      while(angle<=range)
      {
         drawPixel((int)(h+x+0.5),(int)(k-y+0.5),color);

         angle+=0.002;

         x=(r*cos(angle));
         y=(r*sin(angle));
      }
}

void GCLCD::drawPie(uint8_t h,uint8_t k,uint8_t r,int16_t start_angle,int16_t end_angle,uint16_t color)
{

       float angle=(((start_angle<=end_angle)?start_angle:end_angle)*(M_PI/180));
       float range=(((end_angle>start_angle)?end_angle:start_angle)*(M_PI/180));

       float x=(r*cos(angle));
       float y=(r*sin(angle));

      while(angle<=range)
      {
         drawLine(h,k,(int)(h+x+0.5),(int)(k-y+0.5),color);
         angle+=0.0005;

         x=(r*cos(angle));
         y=(r*sin(angle));
      }
}
*/

uint8_t GCLCD::getRotation() {
  return madctl;
}

void GCLCD::setRotation(uint8_t m) {
  madctl = m;
  writecommand(GCLCD_MADCTL);  // memory access control (directions)
  writedata(madctl);  // row address/col address, bottom to top refresh
}

// draw a rectangle
void GCLCD::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		      uint16_t color) {
  // smarter version
  drawHorizontalLine(x, y, w, color);
  drawHorizontalLine(x, y+h-1, w, color);
  drawVerticalLine(x, y, h, color);
  drawVerticalLine(x+w-1, y, h, color);
}

void GCLCD::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		      uint16_t color) {
  // smarter version

  setAddrWindow(x+1, y, x+w, y+h);

  // setup for data
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);

  for (x=0; x < w; x++) {
    for (y=0; y < h; y++) {
      spiwrite(color >> 8);    
      spiwrite(color);    
    }
  }
  digitalWrite(_cs, HIGH);
}

void GCLCD::drawVerticalLine(uint8_t x, uint8_t y, uint8_t length, uint16_t color)
{
  if (x >= width) return;
  if (y+length >= height) length = height-y-1;

  drawFastLine(x,y,length,color,1);
}

void GCLCD::drawHorizontalLine(uint8_t x, uint8_t y, uint8_t length, uint16_t color)
{
  if (y >= height) return;
  if (x+length >= width) length = width-x-1;

  drawFastLine(x,y,length,color,0);
}

void GCLCD::drawFastLine(uint8_t x, uint8_t y, uint8_t length, 
			  uint16_t color, uint8_t rotflag)
{
  if (rotflag) {
    setAddrWindow(x, y, x, y+length);
  } else {
    setAddrWindow(x, y, x+length, y+1);
  }
  // setup for data
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);

  while (length--) {
    spiwrite(color >> 8);    
    spiwrite(color);    
  }
  digitalWrite(_cs, HIGH);
}

// bresenham's algorithm - thx wikpedia
void GCLCD::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
		      uint16_t color) {
  uint16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  uint16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


//////////
/*
uint8_t GCLCD::spiread(void) {
  uint8_t r = 0;
  if (_sid > 0) {
    r = shiftIn(_sid, _sclk, MSBFIRST);
  } else {
    //SID_DDR &= ~_BV(SID);
    //int8_t i;
    //for (i=7; i>=0; i--) {
    //  SCLK_PORT &= ~_BV(SCLK);
    //  r <<= 1;
    //  r |= (SID_PIN >> SID) & 0x1;
    //  SCLK_PORT |= _BV(SCLK);
    //}
    //SID_DDR |= _BV(SID);
    
  }
  return r;
}




void GCLCD::dummyclock(void) {

  if (_sid > 0) {
    digitalWrite(_sclk, LOW);
    digitalWrite(_sclk, HIGH);
  } else {
    // SCLK_PORT &= ~_BV(SCLK);
    //SCLK_PORT |= _BV(SCLK);
  }
}
uint8_t GCLCD::readdata(void) {
  *portOutputRegister(rsport) |= rspin;

  *portOutputRegister(csport) &= ~ cspin;

  uint8_t r = spiread();

  *portOutputRegister(csport) |= cspin;

  return r;

} 

uint8_t GCLCD::readcommand8(uint8_t c) {
  digitalWrite(_rs, LOW);

  *portOutputRegister(csport) &= ~ cspin;

  spiwrite(c);

  digitalWrite(_rs, HIGH);
  pinMode(_sid, INPUT); // input!
  digitalWrite(_sid, LOW); // low
  spiread();
  uint8_t r = spiread();


  *portOutputRegister(csport) |= cspin;



  pinMode(_sid, OUTPUT); // back to output
  return r;
}



uint16_t GCLCD::readcommand16(uint8_t c) {
  digitalWrite(_rs, LOW);
  if (_cs)
    digitalWrite(_cs, LOW);

  spiwrite(c);
  pinMode(_sid, INPUT); // input!
  uint16_t r = spiread();
  r <<= 8;
  r |= spiread();
  if (_cs)
    digitalWrite(_cs, HIGH);

  pinMode(_sid, OUTPUT); // back to output
  return r;
}

uint32_t GCLCD::readcommand32(uint8_t c) {
  digitalWrite(_rs, LOW);
  if (_cs)
    digitalWrite(_cs, LOW);
  spiwrite(c);
  pinMode(_sid, INPUT); // input!

  dummyclock();
  dummyclock();

  uint32_t r = spiread();
  r <<= 8;
  r |= spiread();
  r <<= 8;
  r |= spiread();
  r <<= 8;
  r |= spiread();
  if (_cs)
    digitalWrite(_cs, HIGH);

  pinMode(_sid, OUTPUT); // back to output
  return r;
}

*/

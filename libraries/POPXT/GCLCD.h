// Graphics library by ladyada/adafruit 
// MIT license

#define swap(a, b) { uint16_t t = a; a = b; b = t; }

//#include <WProgram.h>
#include <Arduino.h>

#define GCLCD_NOP 0x0
#define GCLCD_SWRESET 0x01
#define GCLCD_RDDID 0x04
#define GCLCD_RDDST 0x09

#define GCLCD_SLPIN  0x10
#define GCLCD_SLPOUT  0x11
#define GCLCD_PTLON  0x12
#define GCLCD_NORON  0x13

#define GCLCD_INVOFF 0x20
#define GCLCD_INVON 0x21

#define GCLCD_DISPOFF 0x28
#define GCLCD_DISPON 0x29
#define GCLCD_CASET 0x2A
#define GCLCD_RASET 0x2B
#define GCLCD_RAMWR 0x2C
#define GCLCD_RAMRD 0x2E

#define GCLCD_COLMOD 0x3A
#define GCLCD_MADCTL 0x36


#define GCLCD_FRMCTR1 0xB1
#define GCLCD_FRMCTR2 0xB2
#define GCLCD_FRMCTR3 0xB3
#define GCLCD_INVCTR 0xB4
#define GCLCD_DISSET5 0xB6

#define GCLCD_PWCTR1 0xC0
#define GCLCD_PWCTR2 0xC1
#define GCLCD_PWCTR3 0xC2
#define GCLCD_PWCTR4 0xC3
#define GCLCD_PWCTR5 0xC4
#define GCLCD_VMCTR1 0xC5

#define GCLCD_RDID1 0xDA
#define GCLCD_RDID2 0xDB
#define GCLCD_RDID3 0xDC
#define GCLCD_RDID4 0xDD

#define GCLCD_PWCTR6 0xFC

#define GCLCD_GMCTRP1 0xE0
#define GCLCD_GMCTRN1 0xE1


uint16_t __qSqrt(uint16_t rSqr);
static unsigned char GCLCD_TransparentBackground=0; // Default=0 solid background, =1 transparent

class GCLCD {
 public:
  GCLCD(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK);
  GCLCD(uint8_t CS, uint8_t RS);
  void initB(void);
  void initR(void);
  void initS(void);
  void initSBGR(void);
  void initIL(void);
  void initST(void);

  // drawing primitives!
  void pushColor(uint16_t color);
  void drawPixel(uint8_t x, uint8_t y, uint16_t color);
  void drawLine(int16_t x, int16_t y, int16_t x1, int16_t y1, uint16_t color);
  void fillScreen(uint16_t color);
  void drawVerticalLine(uint8_t x0, uint8_t y0, 
			uint8_t length, uint16_t color);
  void drawHorizontalLine(uint8_t x0, uint8_t y0, 
			  uint8_t length, uint16_t color);
  void drawFastLine(uint8_t x0, uint8_t y0, uint8_t l, 
		    uint16_t color, uint8_t flag);
  void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		uint16_t color);
  void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		uint16_t color);
  void drawCircle(uint8_t x0, uint8_t y0, uint8_t r, 
		  uint16_t color);
  void fillCircle(uint8_t x0, uint8_t y0, uint8_t r, 
		  uint16_t color);

  void drawArc(uint8_t h,uint8_t k,uint8_t r,int16_t start_angle,int16_t end_angle,uint16_t color);

//  void drawPie(uint8_t h,uint8_t k,uint8_t r,int16_t start_angle,int16_t end_angle,uint16_t color);

  /*void drawString(uint8_t x, uint8_t y, char *c, 
		  uint16_t color, uint8_t size=1);
  void drawChar(uint8_t x, uint8_t y, char c, 
		      uint16_t color, uint8_t size=1);*/
  void drawString(uint8_t x, uint8_t y, char *c, 
		  uint16_t color,uint16_t bgcolor, uint8_t size=1);
  void drawChar(uint8_t x, uint8_t y, char c, 
		      uint16_t color,uint16_t bgcolor, uint8_t size=1);
  void drawStringTransparent(uint8_t x, uint8_t y, char *c, 
		  uint16_t color, uint8_t size=1);
  void drawCharTransparent(uint8_t x, uint8_t y, char c, 
		      uint16_t color, uint8_t size=1);

  uint8_t width;
  uint8_t height;

  void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
  void setRotation(uint8_t);
  uint8_t getRotation(void);

  void dummyclock(void);
  void writecommand(uint8_t);
  void writedata(uint8_t);
  /*
  // these are not for use, 8-bit protocol only!
  uint8_t readdata(void);
  uint8_t readcommand8(uint8_t);
  uint16_t readcommand16(uint8_t);
  uint32_t readcommand32(uint8_t);
  */

 private:
  void spiwrite(uint8_t);
  //uint8_t spiread(void);

  uint8_t _cs, _rs, _sid, _sclk;
  uint8_t csport, rsport, sidport, sclkport;
  uint8_t cspin, rspin, sidpin, sclkpin;

  uint8_t madctl;
};

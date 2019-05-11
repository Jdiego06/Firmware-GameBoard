#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H


// #include "WProgram.h"

#include "gfxfont.h"
#include "MK64F12.h"
#include <string.h>

  #define Adafruit_GFX_drawPixel MCUFRIEND_kbv_drawPixel 
  // TRANSACTION API / CORE DRAW API
  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  inline void Adafruit_GFX_startWrite(void);
  inline void Adafruit_GFX_writePixel(int16_t x, int16_t y, uint16_t color);
  inline void Adafruit_GFX_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  inline void Adafruit_GFX_writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  inline void Adafruit_GFX_writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  inline void Adafruit_GFX_writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  inline void Adafruit_GFX_endWrite(void);

  inline void Adafruit_GFX_setRotation(uint8_t r);
  inline void Adafruit_GFX_invertDisplay(uint8_t i);

  void Adafruit_GFX_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void Adafruit_GFX_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void Adafruit_GFX_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  void Adafruit_GFX_fillScreen(uint16_t color);
    // Optional and probably not necessary to change
  void Adafruit_GFX_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  void Adafruit_GFX_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

  // These exist only with Adafruit_GFX (no subclass overrides)
  void Adafruit_GFX_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void Adafruit_GFX_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color);
  void Adafruit_GFX_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void Adafruit_GFX_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,int16_t delta, uint16_t color);
  void Adafruit_GFX_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);
  void Adafruit_GFX_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);
  void Adafruit_GFX_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color);
  void Adafruit_GFX_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color);
  void Adafruit_GFX_drawBitmapROM(int16_t x, int16_t y, const uint8_t *bitmap,int16_t w, int16_t h, uint16_t color);
  void Adafruit_GFX_drawBitmapROM1(int16_t x, int16_t y, const uint8_t *bitmap,int16_t w, int16_t h, uint16_t color, uint16_t bg);
  void Adafruit_GFX_drawBitmapROM2(int16_t x, int16_t y,const uint16_t *bitmap, int16_t w, int16_t h,uint16_t color);
  void Adafruit_GFX_drawBitmapRAM(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h, uint16_t color);
  void Adafruit_GFX_drawBitmapRAM1(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h, uint16_t color, uint16_t bg);
  void Adafruit_GFX_drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap,int16_t w, int16_t h, uint16_t color);
  void Adafruit_GFX_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,uint16_t bg, uint8_t size);
  void Adafruit_GFX_setCursor(int16_t x, int16_t y);
  void Adafruit_GFX_setTextColor(uint16_t c);
  void Adafruit_GFX_setTextColorB(uint16_t c, uint16_t bg);
  void Adafruit_GFX_setTextSize(uint8_t s);
  void Adafruit_GFX_setTextWrap(uint8_t w);
  void Adafruit_GFX_cp437(uint8_t x);
  void Adafruit_GFX_setFont(const GFXfont *f);
  void Adafruit_GFX_getTextBounds(char *string, int16_t x, int16_t y,int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

  //inline void   write(uint8_t);
  void Adafruit_GFX_write(uint8_t c);
  void Adafruit_GFX_write_String(uint8_t *message);
  int16_t height(void);
  int16_t width(void);
  uint8_t getRotation(void);

  // get current cursor position (get rotation safe maximum values, using: width() for x, height() for y)
  int16_t getCursorX(void);
  int16_t getCursorY(void);
/*
  int16_t       _x1, _y1; // Coordinates of top-left corner
  uint16_t      _w, _h;
  uint8_t       _textsize;
  uint16_t      _outlinecolor, _fillcolor, _textcolor;
  char          _label[10];

  uint8_t currstate, laststate;
*/


#endif // _ADAFRUIT_GFX_H

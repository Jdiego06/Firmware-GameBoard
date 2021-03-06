/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!

Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
 */

#include "Adafruit_GFX.h"
#include "glcdfont.c"
#include <stdlib.h>

// Many (but maybe not all) non-AVR board installs define macros
// for compatibility with existing PROGMEM-reading AVR code.
// Do our own checks and defines here for good measure...

#include "MCUFRIEND_kbv.h"


#define min(a,b) (((a) < (b)) ? (a) : (b))

#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }



	int16_t    _width    = _WIDTH;
	int16_t    _height   = _HEIGHT;
	uint8_t    rotation  = 0;
	int16_t    cursor_y  = 0; 
	int16_t    cursor_x  = 0;
    uint8_t    textsize  = 1;
    uint16_t   textcolor = 1;
    uint16_t   textbgcolor = 0xFFFF;
    uint8_t    wrap      = true;
    uint8_t    _cp437    = false;
    GFXfont    *gfxFont	 ;

// Bresenham's algorithm - thx wikpedia
void Adafruit_GFX_writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
        uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
        	Adafruit_GFX_writePixel(y0, x0, color);
        } else {
        	Adafruit_GFX_writePixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void Adafruit_GFX_startWrite(){
    // Overwrite in subclasses if desired!
}

void Adafruit_GFX_writePixel(int16_t x, int16_t y, uint16_t color){
    // Overwrite in subclasses if startWrite is defined!
	Adafruit_GFX_drawPixel(x, y, color);
}

// (x,y) is topmost point; if unsure, calling function
// should sort endpoints or call writeLine() instead
void Adafruit_GFX_writeFastVLine(int16_t x, int16_t y,int16_t h, uint16_t color) {
    // Overwrite in subclasses if startWrite is defined!
    // Can be just writeLine(x, y, x, y+h-1, color);
    // or writeFillRect(x, y, 1, h, color);
	Adafruit_GFX_drawFastVLine(x, y, h, color);
}

// (x,y) is leftmost point; if unsure, calling function
// should sort endpoints or call writeLine() instead
void Adafruit_GFX_writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    // Overwrite in subclasses if startWrite is defined!
    // Example: writeLine(x, y, x+w-1, y, color);
    // or writeFillRect(x, y, w, 1, color);
	Adafruit_GFX_drawFastHLine(x, y, w, color);
}

void Adafruit_GFX_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color) {
    // Overwrite in subclasses if desired!
	Adafruit_GFX_fillRect(x,y,w,h,color);
}

void Adafruit_GFX_endWrite(){
    // Overwrite in subclasses if startWrite is defined!
}

// (x,y) is topmost point; if unsure, calling function
// should sort endpoints or call drawLine() instead
void Adafruit_GFX_drawFastVLine(int16_t x, int16_t y,int16_t h, uint16_t color) {
    // Update in subclasses if desired!
	Adafruit_GFX_startWrite();
	Adafruit_GFX_writeLine(x, y, x, y+h-1, color);
	Adafruit_GFX_endWrite();
}

// (x,y) is leftmost point; if unsure, calling function
// should sort endpoints or call drawLine() instead
void Adafruit_GFX_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    // Update in subclasses if desired!
	Adafruit_GFX_startWrite();
	Adafruit_GFX_writeLine(x, y, x+w-1, y, color);
	Adafruit_GFX_endWrite();
}

void Adafruit_GFX_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    // Update in subclasses if desired!
	int16_t i;
	Adafruit_GFX_startWrite();
    for (i=x; i<x+w; i++) {
    	Adafruit_GFX_writeFastVLine(i, y, h, color);
    }
    Adafruit_GFX_endWrite();
}

void Adafruit_GFX_fillScreen(uint16_t color) {
    // Update in subclasses if desired!
	Adafruit_GFX_fillRect(0, 0, _width, _height, color);
}

void Adafruit_GFX_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    // Update in subclasses if desired!
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t(y0, y1);
        Adafruit_GFX_drawFastVLine(x0, y0, y1 - y0 + 1, color);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t(x0, x1);
        Adafruit_GFX_drawFastHLine(x0, y0, x1 - x0 + 1, color);
    } else {
    	Adafruit_GFX_startWrite();
    	Adafruit_GFX_writeLine(x0, y0, x1, y1, color);
    	Adafruit_GFX_endWrite();
    }
}


// Draw a circle outline
void Adafruit_GFX_drawCircle(int16_t x0, int16_t y0, int16_t r,uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    Adafruit_GFX_startWrite();
    Adafruit_GFX_writePixel(x0  , y0+r, color);
    Adafruit_GFX_writePixel(x0  , y0-r, color);
    Adafruit_GFX_writePixel(x0+r, y0  , color);
    Adafruit_GFX_writePixel(x0-r, y0  , color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        Adafruit_GFX_writePixel(x0 + x, y0 + y, color);
        Adafruit_GFX_writePixel(x0 - x, y0 + y, color);
        Adafruit_GFX_writePixel(x0 + x, y0 - y, color);
        Adafruit_GFX_writePixel(x0 - x, y0 - y, color);
        Adafruit_GFX_writePixel(x0 + y, y0 + x, color);
        Adafruit_GFX_writePixel(x0 - y, y0 + x, color);
        Adafruit_GFX_writePixel(x0 + y, y0 - x, color);
        Adafruit_GFX_writePixel(x0 - y, y0 - x, color);
    }
    Adafruit_GFX_endWrite();
}

void Adafruit_GFX_drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
        	Adafruit_GFX_writePixel(x0 + x, y0 + y, color);
        	Adafruit_GFX_writePixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
        	Adafruit_GFX_writePixel(x0 + x, y0 - y, color);
        	Adafruit_GFX_writePixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
        	Adafruit_GFX_writePixel(x0 - y, y0 + x, color);
        	Adafruit_GFX_writePixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
        	Adafruit_GFX_writePixel(x0 - y, y0 - x, color);
        	Adafruit_GFX_writePixel(x0 - x, y0 - y, color);
        }
    }
}

void Adafruit_GFX_fillCircle(int16_t x0, int16_t y0, int16_t r,uint16_t color) {
	Adafruit_GFX_startWrite();
	Adafruit_GFX_writeFastVLine(x0, y0-r, 2*r+1, color);
	Adafruit_GFX_fillCircleHelper(x0, y0, r, 3, 0, color);
	Adafruit_GFX_endWrite();
}

// Used to do circles and roundrects
void Adafruit_GFX_fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
        uint8_t cornername, int16_t delta, uint16_t color) {

    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;

        if (cornername & 0x1) {
        	Adafruit_GFX_writeFastVLine(x0+x, y0-y, 2*y+1+delta, color);
        	Adafruit_GFX_writeFastVLine(x0+y, y0-x, 2*x+1+delta, color);
        }
        if (cornername & 0x2) {
        	Adafruit_GFX_writeFastVLine(x0-x, y0-y, 2*y+1+delta, color);
        	Adafruit_GFX_writeFastVLine(x0-y, y0-x, 2*x+1+delta, color);
        }
    }
}

// Draw a rectangle
void Adafruit_GFX_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	Adafruit_GFX_startWrite();
	Adafruit_GFX_writeFastHLine(x, y, w, color);
	Adafruit_GFX_writeFastHLine(x, y+h-1, w, color);
	Adafruit_GFX_writeFastVLine(x, y, h, color);
	Adafruit_GFX_writeFastVLine(x+w-1, y, h, color);
	Adafruit_GFX_endWrite();
}

// Draw a rounded rectangle
void Adafruit_GFX_drawRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r, uint16_t color) {
    // smarter version
	Adafruit_GFX_startWrite();
	Adafruit_GFX_writeFastHLine(x+r  , y    , w-2*r, color); // Top
	Adafruit_GFX_writeFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
	Adafruit_GFX_writeFastVLine(x    , y+r  , h-2*r, color); // Left
	Adafruit_GFX_writeFastVLine(x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
	Adafruit_GFX_drawCircleHelper(x+r    , y+r    , r, 1, color);
	Adafruit_GFX_drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	Adafruit_GFX_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	Adafruit_GFX_drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
	Adafruit_GFX_endWrite();
}

// Fill a rounded rectangle
void Adafruit_GFX_fillRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r, uint16_t color) {
    // smarter version
	Adafruit_GFX_startWrite();
	Adafruit_GFX_writeFillRect(x+r, y, w-2*r, h, color);

    // draw four corners
	Adafruit_GFX_fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	Adafruit_GFX_fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
	Adafruit_GFX_endWrite();
}

// Draw a triangle
void Adafruit_GFX_drawTriangle(int16_t x0, int16_t y0,
        int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	Adafruit_GFX_drawLine(x0, y0, x1, y1, color);
	Adafruit_GFX_drawLine(x1, y1, x2, y2, color);
	Adafruit_GFX_drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void Adafruit_GFX_fillTriangle(int16_t x0, int16_t y0,
        int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {

    int16_t a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }

    Adafruit_GFX_startWrite();
    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        Adafruit_GFX_writeFastHLine(a, y0, b-a+1, color);
        Adafruit_GFX_endWrite();
        return;
    }

    int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
    int32_t
    sa   = 0,
    sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
         */
        if(a > b) _swap_int16_t(a,b);
        Adafruit_GFX_writeFastHLine(a, y, b-a+1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
         */
        if(a > b) _swap_int16_t(a,b);
        Adafruit_GFX_writeFastHLine(a, y, b-a+1, color);
    }
    Adafruit_GFX_endWrite();
}

// Draw a 1-bit image (bitmap) at the specified (x,y) position from the
// provided bitmap buffer (must be PROGMEM memory) using the specified
// foreground color (unset bits are transparent).
void Adafruit_GFX_drawBitmapROM(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte = 0;

    Adafruit_GFX_startWrite();
    for(j=0; j<h; j++) {
        for(i=0; i<w; i++) {
            if(i & 7) byte <<= 1;
            else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
            if(byte & 0x80) Adafruit_GFX_writePixel(x+i, y+j, color);
        }
    }
    Adafruit_GFX_endWrite();
}

// Draw a 1-bit image (bitmap) at the specified (x,y) position from the
// provided bitmap buffer (must be PROGMEM memory) using the specified
// foreground (for set bits) and background (for clear bits) colors.
void Adafruit_GFX_drawBitmapROM1(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte = 0;

    Adafruit_GFX_startWrite();
    for(j=0; j<h; j++) {
        for(i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
            if(byte & 0x80) Adafruit_GFX_writePixel(x+i, y+j, color);
            else            Adafruit_GFX_writePixel(x+i, y+j, bg);
        }
    }
    Adafruit_GFX_endWrite();
}


void Adafruit_GFX_drawBitmapROM2(int16_t x, int16_t y,const uint16_t *bitmap, int16_t w, int16_t h,uint16_t color) {

  int16_t i, j;
  //int16_t color2;
  const int16_t * ptr=( const int16_t *)bitmap;
  //byteWidth = (w + 7) / 8;
  Adafruit_GFX_startWrite();
  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      //if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
    	//color2=pgm_read_word(bitmap + (j * w) + i);
    	if(*ptr!=color){
    		Adafruit_GFX_drawPixel(x+i, y+j, *ptr);
    	}//else{
    		//Adafruit_GFX_drawPixel(x+i, y+j, 0xFFFF);
    	//}
    	ptr++;
    }
  }
  Adafruit_GFX_endWrite();
}
// drawBitmap() variant for RAM-resident (not PROGMEM) bitmaps.
void Adafruit_GFX_drawBitmapRAM(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte = 0;

    Adafruit_GFX_startWrite();
    for(j=0; j<h; j++) {
        for(i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = bitmap[j * byteWidth + i / 8];
            if(byte & 0x80) Adafruit_GFX_writePixel(x+i, y+j, color);
        }
    }
    Adafruit_GFX_endWrite();
}

// drawBitmap() variant w/background for RAM-resident (not PROGMEM) bitmaps.
void Adafruit_GFX_drawBitmapRAM1(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte = 0;

    Adafruit_GFX_startWrite();
    for(j=0; j<h; j++) {
        for(i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = bitmap[j * byteWidth + i / 8];
            if(byte & 0x80) Adafruit_GFX_writePixel(x+i, y+j, color);
            else            Adafruit_GFX_writePixel(x+i, y+j, bg);
        }
    }
    Adafruit_GFX_endWrite();
}

//Draw XBitMap Files (*.xbm), exported from GIMP,
//Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
//C Array can be directly used with this function
void Adafruit_GFX_drawXBitmap(int16_t x, int16_t y,
        const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte = 0;

    Adafruit_GFX_startWrite();
    for(j=0; j<h; j++) {
        for(i=0; i<w; i++ ) {
            if(i & 7) byte >>= 1;
            else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
            if(byte & 0x01) Adafruit_GFX_writePixel(x+i, y+j, color);
        }
    }
    Adafruit_GFX_endWrite();
}

// Draw a character
void Adafruit_GFX_drawChar(int16_t x, int16_t y, unsigned char c,uint16_t color, uint16_t bg, uint8_t size) {

    if(!gfxFont) { // 'Classic' built-in font
    	int8_t i;
    	int8_t j;
        if((x >= _width)            || // Clip right
                (y >= _height)           || // Clip bottom
                ((x + 6 * size - 1) < 0) || // Clip left
                ((y + 8 * size - 1) < 0))   // Clip top
            return;

        if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

        Adafruit_GFX_startWrite();
        for(i=0; i<6; i++ ) {
            uint8_t line;
            if(i < 5) line = pgm_read_byte(font+(c*5)+i);
            else      line = 0x0;
            for(j=0; j<8; j++, line >>= 1) {
                if(line & 0x1) {
                    if(size == 1) Adafruit_GFX_writePixel(x+i, y+j, color);
                    else          Adafruit_GFX_writeFillRect(x+(i*size), y+(j*size), size, size, color);
                } else if(bg != color) {
                    if(size == 1) Adafruit_GFX_writePixel(x+i, y+j, bg);
                    else          Adafruit_GFX_writeFillRect(x+i*size, y+j*size, size, size, bg);
                }
            }
        }
        Adafruit_GFX_endWrite();

    } else { // Custom font

        // Character is assumed previously filtered by write() to eliminate
        // newlines, returns, non-printable characters, etc.  Calling drawChar()
        // directly with 'bad' characters of font may cause mayhem!

        c -= pgm_read_byte(&gfxFont->first);
        GFXglyph *glyph  = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
        uint8_t  *bitmap = (uint8_t *)pgm_read_pointer(&gfxFont->bitmap);

        uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
        uint8_t  w  = pgm_read_byte(&glyph->width),
                h  = pgm_read_byte(&glyph->height);
        int8_t   xo = pgm_read_byte(&glyph->xOffset),
                yo = pgm_read_byte(&glyph->yOffset);
        uint8_t  xx, yy, bits = 0, bit = 0;
        int16_t  xo16 = 0, yo16 = 0;

        if(size > 1) {
            xo16 = xo;
            yo16 = yo;
        }

        // Todo: Add character clipping here

        // NOTE: THERE IS NO 'BACKGROUND' COLOR OPTION ON CUSTOM FONTS.
        // THIS IS ON PURPOSE AND BY DESIGN.  The background color feature
        // has typically been used with the 'classic' font to overwrite old
        // screen contents with new data.  This ONLY works because the
        // characters are a uniform size; it's not a sensible thing to do with
        // proportionally-spaced fonts with glyphs of varying sizes (and that
        // may overlap).  To replace previously-drawn text when using a custom
        // font, use the getTextBounds() function to determine the smallest
        // rectangle encompassing a string, erase the area with fillRect(),
        // then draw new text.  This WILL infortunately 'blink' the text, but
        // is unavoidable.  Drawing 'background' pixels will NOT fix this,
        // only creates a new set of problems.  Have an idea to work around
        // this (a canvas object type for MCUs that can afford the RAM and
        // displays supporting setAddrWindow() and pushColors()), but haven't
        // implemented this yet.

        Adafruit_GFX_startWrite();
        for(yy=0; yy<h; yy++) {
            for(xx=0; xx<w; xx++) {
                if(!(bit++ & 7)) {
                    bits = pgm_read_byte(&bitmap[bo++]);
                }
                if(bits & 0x80) {
                    if(size == 1) {
                    	Adafruit_GFX_writePixel(x+xo+xx, y+yo+yy, color);
                    } else {
                    	Adafruit_GFX_writeFillRect(x+(xo16+xx)*size, y+(yo16+yy)*size, size, size, color);
                    }
                }
                bits <<= 1;
            }
        }
        Adafruit_GFX_endWrite();

    } // End classic vs custom font
}


void Adafruit_GFX_write(uint8_t c) {
    if(!gfxFont) { // 'Classic' built-in font

        if(c == '\n') {
            cursor_y += textsize*8;
            cursor_x  = 0;
        } else if(c == '\r') {
            // skip em
        } else {
            if(wrap && ((cursor_x + textsize * 6) >= _width)) { // Heading off edge?
                cursor_x  = 0;            // Reset x to zero
                cursor_y += textsize * 8; // Advance y one line
            }
            Adafruit_GFX_drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
            cursor_x += textsize * 6;
        }

    } else { // Custom font

        if(c == '\n') {
            cursor_x  = 0;
            cursor_y += (int16_t)textsize *
                    (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
        } else if(c != '\r') {
            uint8_t first = pgm_read_byte(&gfxFont->first);
            if((c >= first) && (c <= (uint8_t)pgm_read_byte(&gfxFont->last))) {
                uint8_t   c2    = c - pgm_read_byte(&gfxFont->first);
                GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c2]);
                uint8_t   w     = pgm_read_byte(&glyph->width),
                        h     = pgm_read_byte(&glyph->height);
                if((w > 0) && (h > 0)) { // Is there an associated bitmap?
                    int16_t xo = (int8_t)pgm_read_byte(&glyph->xOffset); // sic
                    if(wrap && ((cursor_x + textsize * (xo + w)) >= _width)) {
                        // Drawing character would go off right edge; wrap to new line
                        cursor_x  = 0;
                        cursor_y += (int16_t)textsize *
                                (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
                    }
                    Adafruit_GFX_drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
                }
                cursor_x += pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize;
            }
        }

    }
}

void Adafruit_GFX_write_String(uint8_t *message){
	uint8_t i=0, len=0;
	len= strlen((const char *)message);
	for(i=0; i<len; i++){
		Adafruit_GFX_write(message[i]);
	}


}
void Adafruit_GFX_setCursor(int16_t x, int16_t y) {
    cursor_x = x;
    cursor_y = y;
}

int16_t Adafruit_GFX_getCursorX(void) {
    return cursor_x;
}

int16_t Adafruit_GFX_getCursorY(void) {
    return cursor_y;
}

void Adafruit_GFX_setTextSize(uint8_t s) {
    textsize = (s > 0) ? s : 1;
}

void Adafruit_GFX_setTextColor(uint16_t c) {
    // For 'transparent' background, we'll set the bg
    // to the same as fg instead of using a flag
    textcolor   = c; 
    textbgcolor = c;
}

void Adafruit_GFX_setTextColorB(uint16_t c, uint16_t b) {
    textcolor   = c;
    textbgcolor = b;
}

void Adafruit_GFXsetTextWrap(uint8_t w) {
    wrap = w;
}

uint8_t Adafruit_GFX_getRotation(void) {
    return rotation;
}

void Adafruit_GFX_setRotation(uint8_t x) {
    rotation = (x & 3);
    switch(rotation) {
        case 0:
        case 2:
            _width  = _WIDTH;
            _height = _HEIGHT;
            break;
        case 1:
        case 3:
            _width  = _HEIGHT;
            _height = _WIDTH;
            break;
    }
}

// Enable (or disable) Code Page 437-compatible charset.
// There was an error in glcdfont.c for the longest time -- one character
// (#176, the 'light shade' block) was missing -- this threw off the index
// of every character that followed it.  But a TON of code has been written
// with the erroneous character indices.  By default, the library uses the
// original 'wrong' behavior and old sketches will still work.  Pass 'true'
// to this function to use correct CP437 character values in your code.
void Adafruit_GFX_cp437(uint8_t x) {
    _cp437 = x;
}

void Adafruit_GFX_setFont(const GFXfont *f) {
    if(f) {          // Font struct pointer passed in?
        if(!gfxFont) { // And no current font struct?
            // Switching from classic to new font behavior.
            // Move cursor pos down 6 pixels so it's on baseline.
            cursor_y += 6;
        }
    } else if(gfxFont) { // NULL passed.  Current font struct defined?
        // Switching from new to classic font behavior.
        // Move cursor pos up 6 pixels so it's at top-left of char.
        cursor_y -= 6;
    }
    gfxFont = (GFXfont *)f;
}

// Pass string and a cursor position, returns UL corner and W,H.
void Adafruit_GFX_getTextBounds(char *str, int16_t x, int16_t y,
        int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
    uint8_t c; // Current character

    *x1 = x;
    *y1 = y;
    *w  = *h = 0;

    if(gfxFont) {

        GFXglyph *glyph;
        uint8_t   first = pgm_read_byte(&gfxFont->first),
                last  = pgm_read_byte(&gfxFont->last),
                gw, gh, xa;
        int8_t    xo, yo;
        int16_t   minx = _width, miny = _height, maxx = -1, maxy = -1,
                gx1, gy1, gx2, gy2, ts = (int16_t)textsize,
                ya = ts * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);

        while((c = *str++)) {
            if(c != '\n') { // Not a newline
                if(c != '\r') { // Not a carriage return, is normal char
                    if((c >= first) && (c <= last)) { // Char present in current font
                        c    -= first;
                        glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
                        gw    = pgm_read_byte(&glyph->width);
                        gh    = pgm_read_byte(&glyph->height);
                        xa    = pgm_read_byte(&glyph->xAdvance);
                        xo    = pgm_read_byte(&glyph->xOffset);
                        yo    = pgm_read_byte(&glyph->yOffset);
                        if(wrap && ((x + (((int16_t)xo + gw) * ts)) >= _width)) {
                            // Line wrap
                            x  = 0;  // Reset x to 0
                            y += ya; // Advance y by 1 line
                        }
                        gx1 = x   + xo * ts;
                        gy1 = y   + yo * ts;
                        gx2 = gx1 + gw * ts - 1;
                        gy2 = gy1 + gh * ts - 1;
                        if(gx1 < minx) minx = gx1;
                        if(gy1 < miny) miny = gy1;
                        if(gx2 > maxx) maxx = gx2;
                        if(gy2 > maxy) maxy = gy2;
                        x += xa * ts;
                    }
                } // Carriage return = do nothing
            } else { // Newline
                x  = 0;  // Reset x
                y += ya; // Advance y by 1 line
            }
        }
        // End of string
        *x1 = minx;
        *y1 = miny;
        if(maxx >= minx) *w  = maxx - minx + 1;
        if(maxy >= miny) *h  = maxy - miny + 1;

    } else { // Default font

        uint16_t lineWidth = 0, maxWidth = 0; // Width of current, all lines

        while((c = *str++)) {
            if(c != '\n') { // Not a newline
                if(c != '\r') { // Not a carriage return, is normal char
                    if(wrap && ((x + textsize * 6) >= _width)) {
                        x  = 0;            // Reset x to 0
                        y += textsize * 8; // Advance y by 1 line
                        if(lineWidth > maxWidth) maxWidth = lineWidth; // Save widest line
                        lineWidth  = textsize * 6; // First char on new line
                    } else { // No line wrap, just keep incrementing X
                        lineWidth += textsize * 6; // Includes interchar x gap
                    }
                } // Carriage return = do nothing
            } else { // Newline
                x  = 0;            // Reset x to 0
                y += textsize * 8; // Advance y by 1 line
                if(lineWidth > maxWidth) maxWidth = lineWidth; // Save widest line
                lineWidth = 0;     // Reset lineWidth for new line
            }
        }
        // End of string
        if(lineWidth) y += textsize * 8; // Add height of last (or only) line
        if(lineWidth > maxWidth) maxWidth = lineWidth; // Is the last or only line the widest?
        *w = maxWidth - 1;               // Don't include last interchar x gap
        *h = y - *y1;

    } // End classic vs custom font
}

// Return the size of the display (per current rotation)
int16_t Adafruit_GFX_width(void) {
    return _width;
}

int16_t Adafruit_GFX_height(void) {
    return _height;
}

void Adafruit_GFX_invertDisplay(uint8_t i) {
    // Do nothing, must be subclassed if supported by hardware
}

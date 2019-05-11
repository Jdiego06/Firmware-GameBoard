#ifndef MCUFRIEND_KBV_H_
#define MCUFRIEND_KBV_H_   295
#include "TFT_config.h"

    #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
    #define pgm_read_word(addr) (*(const unsigned short *)(addr))
 	#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
 	#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))

	//#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))

	#define _HEIGHT 320
	#define _WIDTH  240
	#define false 0
	#define true 1
	
	void     MCUFRIEND_kbv_reset(void);      
	void 	 MCUFRIEND_kbv_init(void); 
	void     MCUFRIEND_kbv_begin(uint16_t ID);                      
	void     MCUFRIEND_kbv_drawPixel(int16_t x, int16_t y, uint16_t color);  // and these three
	void     MCUFRIEND_kbv_WriteCmdData(uint16_t cmd, uint16_t dat);                
    void     MCUFRIEND_kbv_pushCommand(uint16_t cmd, uint8_t * block, int8_t N);
	uint16_t MCUFRIEND_kbv_color565(uint8_t r, uint8_t g, uint8_t b);
	uint16_t MCUFRIEND_kbv_readID(void);
	void     MCUFRIEND_kbv_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void     MCUFRIEND_kbv_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void     MCUFRIEND_kbv_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	void     MCUFRIEND_kbv_fillScreen(uint16_t color);                                     
	void     MCUFRIEND_kbv_setRotation(uint8_t r);
    void     MCUFRIEND_kbv_invertDisplay(uint8_t i);

	uint16_t MCUFRIEND_kbv_readReg(uint16_t reg, int8_t index);//index default=0
	int16_t  MCUFRIEND_kbv_readGRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h);
	uint16_t MCUFRIEND_kbv_readPixel(int16_t x, int16_t y);// { uint16_t color; readGRAM(x, y, &color, 1, 1); return color; }
	void     MCUFRIEND_kbv_setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
	void     MCUFRIEND_kbv_pushColors(uint16_t *block, int16_t n, uint8_t first);
	void     MCUFRIEND_kbv_pushColors1(uint8_t *block, int16_t n, uint8_t first);//diferent version
	void     MCUFRIEND_kbv_pushColors2(const uint8_t *block, int16_t n, uint8_t first, uint8_t bigend );// diferent version bigend default= false
    void     MCUFRIEND_kbv_vertScroll(int16_t top, int16_t scrollines, int16_t offset);

	uint32_t MCUFRIEND_kbv_readReg32(uint16_t reg);
	uint32_t MCUFRIEND_kbv_readReg40(uint16_t reg);

//};
	void MCUFRIEND_kbv_fillBMP(const unsigned short *bmp_ptr);
	void MCUFRIEND_kbv_print_tail( const unsigned short *bmp_ptr,int16_t x, int16_t y, int16_t w, int16_t h);

#endif

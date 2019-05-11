#ifndef _BOARD_H_
#define _BOARD_H_

#include "MK64F12.h"
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* The board name */
#define BOARD_NAME "GAME-BOARD"
#define OUTPUTPORT 1
#define INPUTPORT 0
//---------------------------------------------------------
// | NAME   | FRDM |  GAME_BOARD |
// | LCD_D0 | PTA0 |   PTE24     |
//---------------------------------------------------------
#define LCD_DO_PDDR     (GPIOE->PDDR)
#define LCD_DO_PDOR     (GPIOE->PDOR)
#define LCD_DO_PDIR     (GPIOE->PDIR)
#define LCD_DO_PCR		PORTE->PCR[24]
#define LCD_DO_PIN      24


#define LCD_D0_In() 	BITBAND_REG(LCD_DO_PDDR,LCD_DO_PIN)=0
#define LCD_D0_Out() 	BITBAND_REG(LCD_DO_PDDR,LCD_DO_PIN)=1
#define LCD_D0_Clear() 	BITBAND_REG(LCD_DO_PDOR,LCD_DO_PIN)=0
#define LCD_D0_Set() 	BITBAND_REG(LCD_DO_PDOR,LCD_DO_PIN)=1
#define LCD_D0_R 		BITBAND_REG(LCD_DO_PDIR,LCD_DO_PIN)
#define LCD_D0_W 		BITBAND_REG(LCD_DO_PDOR,LCD_DO_PIN)

//---------------------------------------------------------
// | NAME   | FRDM |  GAME_BOARD |
// | LCD_D1 | PTC4 |  PTE5       |
//---------------------------------------------------------
#define LCD_D1_PDDR     GPIOE->PDDR
#define LCD_D1_PDOR     GPIOE->PDOR
#define LCD_D1_PDIR     GPIOE->PDIR
#define LCD_D1_PCR		PORTE->PCR[5]
#define LCD_D1_PIN      5


#define LCD_D1_In() 	BITBAND_REG(LCD_D1_PDDR,LCD_D1_PIN)=0
#define LCD_D1_Out() 	BITBAND_REG(LCD_D1_PDDR,LCD_D1_PIN)=1
#define LCD_D1_Clear() 	BITBAND_REG(LCD_D1_PDOR,LCD_D1_PIN)=0
#define LCD_D1_Set() 	BITBAND_REG(LCD_D1_PDOR,LCD_D1_PIN)=1
#define LCD_D1_R 		BITBAND_REG(LCD_D1_PDIR,LCD_D1_PIN)
#define LCD_D1_W 		BITBAND_REG(LCD_D1_PDOR,LCD_D1_PIN)
//----------------------------------------------------------
// | NAME   | FRDM |  GAME_BOARD |
// | LCD_D2 | PTB9 |  PTA14      |
//---------------------------------------------------------
#define LCD_D2_PDDR     GPIOA->PDDR
#define LCD_D2_PDOR     GPIOA->PDOR
#define LCD_D2_PDIR     GPIOA->PDIR
#define LCD_D2_PCR		PORTA->PCR[14]
#define LCD_D2_PIN      14


#define LCD_D2_In() 	BITBAND_REG(LCD_D2_PDDR,LCD_D2_PIN)=0
#define LCD_D2_Out() 	BITBAND_REG(LCD_D2_PDDR,LCD_D2_PIN)=1
#define LCD_D2_Clear() 	BITBAND_REG(LCD_D2_PDOR,LCD_D2_PIN)=0
#define LCD_D2_Set() 	BITBAND_REG(LCD_D2_PDOR,LCD_D2_PIN)=1
#define LCD_D2_R 		BITBAND_REG(LCD_D2_PDIR,LCD_D2_PIN)
#define LCD_D2_W 		BITBAND_REG(LCD_D2_PDOR,LCD_D2_PIN)

//----------------------------------------------------------
// | NAME   | FRDM |  GAME_BOARD |
// | LCD_D3 | PTA1 |  PTA13      |
//---------------------------------------------------------
#define LCD_D3_PDDR     GPIOA->PDDR
#define LCD_D3_PDOR     GPIOA->PDOR
#define LCD_D3_PDIR     GPIOA->PDIR
#define LCD_D3_PCR		PORTA->PCR[13]
#define LCD_D3_PIN      13


#define LCD_D3_In() 	BITBAND_REG(LCD_D3_PDDR,LCD_D3_PIN)=0
#define LCD_D3_Out() 	BITBAND_REG(LCD_D3_PDDR,LCD_D3_PIN)=1
#define LCD_D3_Clear() 	BITBAND_REG(LCD_D3_PDOR,LCD_D3_PIN)=0
#define LCD_D3_Set() 	BITBAND_REG(LCD_D3_PDOR,LCD_D3_PIN)=1
#define LCD_D3_R 		BITBAND_REG(LCD_D3_PDIR,LCD_D3_PIN)
#define LCD_D3_W 		BITBAND_REG(LCD_D3_PDOR,LCD_D3_PIN)

//----------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_D4 | PTB23 |  PTA12      |
//---------------------------------------------------------
#define LCD_D4_PDDR     GPIOA->PDDR
#define LCD_D4_PDOR     GPIOA->PDOR
#define LCD_D4_PDIR     GPIOA->PDIR
#define LCD_D4_PCR		PORTA->PCR[12]
#define LCD_D4_PIN      12


#define LCD_D4_In() 	BITBAND_REG(LCD_D4_PDDR,LCD_D4_PIN)=0
#define LCD_D4_Out() 	BITBAND_REG(LCD_D4_PDDR,LCD_D4_PIN)=1
#define LCD_D4_Clear() 	BITBAND_REG(LCD_D4_PDOR,LCD_D4_PIN)=0
#define LCD_D4_Set() 	BITBAND_REG(LCD_D4_PDOR,LCD_D4_PIN)=1
#define LCD_D4_R 		BITBAND_REG(LCD_D4_PDIR,LCD_D4_PIN)
#define LCD_D4_W 		BITBAND_REG(LCD_D4_PDOR,LCD_D4_PIN)

//----------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_D5 | PTA2  |  PTA5       |
//---------------------------------------------------------
#define LCD_D5_PDDR     GPIOA->PDDR
#define LCD_D5_PDOR     GPIOA->PDOR
#define LCD_D5_PDIR     GPIOA->PDIR
#define LCD_D5_PCR		PORTA->PCR[5]
#define LCD_D5_PIN      5


#define LCD_D5_In() 	BITBAND_REG(LCD_D5_PDDR,LCD_D5_PIN)=0
#define LCD_D5_Out() 	BITBAND_REG(LCD_D5_PDDR,LCD_D5_PIN)=1
#define LCD_D5_Clear() 	BITBAND_REG(LCD_D5_PDOR,LCD_D5_PIN)=0
#define LCD_D5_Set() 	BITBAND_REG(LCD_D5_PDOR,LCD_D5_PIN)=1
#define LCD_D5_R 		BITBAND_REG(LCD_D5_PDIR,LCD_D5_PIN)
#define LCD_D5_W 		BITBAND_REG(LCD_D5_PDOR,LCD_D5_PIN)
//----------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_D6 | PTC2  |  PTE26      |
//---------------------------------------------------------
#define LCD_D6_PDDR     GPIOE->PDDR
#define LCD_D6_PDOR     GPIOE->PDOR
#define LCD_D6_PDIR     GPIOE->PDIR
#define LCD_D6_PCR		PORTE->PCR[26]
#define LCD_D6_PIN      26


#define LCD_D6_In() 	BITBAND_REG(LCD_D6_PDDR,LCD_D6_PIN)=0
#define LCD_D6_Out() 	BITBAND_REG(LCD_D6_PDDR,LCD_D6_PIN)=1
#define LCD_D6_Clear() 	BITBAND_REG(LCD_D6_PDOR,LCD_D6_PIN)=0
#define LCD_D6_Set() 	BITBAND_REG(LCD_D6_PDOR,LCD_D6_PIN)=1
#define LCD_D6_R 		BITBAND_REG(LCD_D6_PDIR,LCD_D6_PIN)
#define LCD_D6_W 		BITBAND_REG(LCD_D6_PDOR,LCD_D6_PIN)

//----------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_D7 | PTC3  |  PTE25      |
//---------------------------------------------------------
#define LCD_D7_PDDR     GPIOE->PDDR
#define LCD_D7_PDOR     GPIOE->PDOR
#define LCD_D7_PDIR     GPIOE->PDIR
#define LCD_D7_PCR		PORTE->PCR[25]
#define LCD_D7_PIN      25


#define LCD_D7_In() 	BITBAND_REG(LCD_D7_PDDR,LCD_D7_PIN)=0
#define LCD_D7_Out() 	BITBAND_REG(LCD_D7_PDDR,LCD_D7_PIN)=1
#define LCD_D7_Clear() 	BITBAND_REG(LCD_D7_PDOR,LCD_D7_PIN)=0
#define LCD_D7_Set() 	BITBAND_REG(LCD_D7_PDOR,LCD_D7_PIN)=1
#define LCD_D7_R 		BITBAND_REG(LCD_D7_PDIR,LCD_D7_PIN)
#define LCD_D7_W 		BITBAND_REG(LCD_D7_PDOR,LCD_D7_PIN)
//----------------------------------------------------------
// Pixel read operations require a minimum 400 nS delay from RD_ACTIVE
// to polling the input pins.  At 16 MHz, one machine cycle is 62.5 nS.
// This code burns 7 cycles (437.5 nS) doing nothing; the RJMPs are
// equivalent to two NOPs each, final NOP burns the 7th cycle, and the
// last line is a radioactive mutant emoticon.
#define DELAY7       asm nop,asm nop,asm nop,asm nop,asm nop,asm nop,asm nop,asm nop,asm nop,asm nop

// Control signals are ACTIVE LOW (idle is HIGH)
// Command/Data: LOW = command, HIGH = data
// These are single-instruction operations and always inline

//---------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_RD | PTB2  |  PTC2       |
//----------------------------------------------------------
#define LCD_RD_PDDR     GPIOC->PDDR
#define LCD_RD_PDOR     GPIOC->PDOR
#define LCD_RD_PCR		PORTC->PCR[2]
#define LCD_RD_PIN      2

#define LCD_RD_Out() 	BITBAND_REG(LCD_RD_PDDR,LCD_RD_PIN)=1
#define LCD_RD_Clear() 	BITBAND_REG(LCD_RD_PDOR,LCD_RD_PIN)=0
#define LCD_RD_Set() 	BITBAND_REG(LCD_RD_PDOR,LCD_RD_PIN)=1

#define RD_ACTIVE  		LCD_RD_Clear()
#define RD_IDLE    		LCD_RD_Set()
#define RD_OUTPUT		LCD_RD_Out()

//---------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_WR | PTB3  |  PTC1       | SLOULD BE ADC FOR TOUCH
//----------------------------------------------------------
#define LCD_WR_PDDR     GPIOC->PDDR
#define LCD_WR_PDOR     GPIOC->PDOR
#define LCD_WR_PCR		PORTC->PCR[1]
#define LCD_WR_PIN      1

#define LCD_WR_Out() 	BITBAND_REG(LCD_WR_PDDR,LCD_WR_PIN)=1
#define LCD_WR_Clear()  BITBAND_REG(LCD_WR_PDOR,LCD_WR_PIN)=0
#define LCD_WR_Set() 	BITBAND_REG(LCD_WR_PDOR,LCD_WR_PIN)=1

#define WR_ACTIVE  		LCD_WR_Clear()
#define WR_IDLE    		LCD_WR_Set()
#define WR_OUTPUT		LCD_WR_Out()

//---------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_RS | PTB10 |  PTC0       | SLOULD BE ADC FOR TOUCH
//----------------------------------------------------------
#define LCD_RS_PDDR     GPIOC->PDDR
#define LCD_RS_PDOR     GPIOC->PDOR
#define LCD_RS_PCR		PORTC->PCR[0]
#define LCD_RS_PIN      0

#define LCD_RS_Out() 	BITBAND_REG(LCD_RS_PDDR,LCD_RS_PIN)=1
#define LCD_RS_Clear()  BITBAND_REG(LCD_RS_PDOR,LCD_RS_PIN)=0
#define LCD_RS_Set() 	BITBAND_REG(LCD_RS_PDOR,LCD_RS_PIN)=1

#define CD_COMMAND  	LCD_RS_Clear()
#define CD_DATA    		LCD_RS_Set()
#define CD_OUTPUT		LCD_RS_Out()

//---------------------------------------------------------
// | NAME   | FRDM  |  GAME_BOARD |
// | LCD_CS | PTB11 |  PTB23      | SLOULD BE ADC FOR TOUCH
//----------------------------------------------------------
#define LCD_CS_PDDR     GPIOB->PDDR
#define LCD_CS_PDOR     GPIOB->PDOR
#define LCD_CS_PCR		PORTB->PCR[23]
#define LCD_CS_PIN      23

#define LCD_CS_Out() 	BITBAND_REG(LCD_CS_PDDR,LCD_CS_PIN)=1
#define LCD_CS_Clear()  BITBAND_REG(LCD_CS_PDOR,LCD_CS_PIN)=0
#define LCD_CS_Set() 	BITBAND_REG(LCD_CS_PDOR,LCD_CS_PIN)=1

#define CS_ACTIVE  		LCD_CS_Clear()
#define CS_IDLE    		LCD_CS_Set()
#define CS_OUTPUT		LCD_CS_Out()

//---------------------------------------------------------
// | NAME    | FRDM  |  GAME_BOARD |
// | LCD_RST | PTC11 |  PTB22      | SLOULD BE ADC FOR TOUCH
//----------------------------------------------------------
#define LCD_RST_PDDR     GPIOB->PDDR
#define LCD_RST_PDOR     GPIOB->PDOR
#define LCD_RST_PCR		 PORTB->PCR[22]
#define LCD_RST_PIN      22

#define LCD_RST_Out() 	BITBAND_REG(LCD_RST_PDDR,LCD_RST_PIN)=1
#define LCD_RST_Clear() BITBAND_REG(LCD_RST_PDOR,LCD_RST_PIN)=0
#define LCD_RST_Set() 	BITBAND_REG(LCD_RST_PDOR,LCD_RST_PIN)=1

#define RESET_ACTIVE  	LCD_RST_Clear()
#define RESET_IDLE    	LCD_RST_Set()
#define RESET_OUTPUT	LCD_RST_Out()


#define WRITE_DELAY 	//{ WR_ACTIVE;}//; WR_ACTIVE; WR_ACTIVE; WR_ACTIVE; }
#define READ_DELAY  	{ RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; }

// General macros.   IOCLR registers are 1 cycle when optimised.

#define read_8()		(LCD_D0_R<<0)|(LCD_D1_R<<1)|(LCD_D2_R<<2)|(LCD_D3_R<<3)|(LCD_D4_R<<4)|(LCD_D5_R<<5)|(LCD_D6_R<<6)|(LCD_D7_R<<7);
#define write_8(d)   	LCD_D0_W=(d)>>0; LCD_D1_W=(d)>>1; LCD_D2_W=(d)>>2; LCD_D3_W=(d)>>3; LCD_D4_W=(d)>>4; LCD_D5_W=(d)>>5; LCD_D6_W=(d)>>6; LCD_D7_W=(d)>>7;
#define setWriteDir()   LCD_D0_Out(); LCD_D1_Out(); LCD_D2_Out(); LCD_D3_Out(); LCD_D4_Out(); LCD_D5_Out(); LCD_D6_Out(); LCD_D7_Out();
#define setReadDir()	LCD_D0_In(); LCD_D1_In(); LCD_D2_In(); LCD_D3_In(); LCD_D4_In(); LCD_D5_In(); LCD_D6_In(); LCD_D7_In();
#define WR_STROBE 		{ WR_ACTIVE; WR_IDLE; }         					// PWLW=TWRL=50ns
#define RD_STROBE 		RD_IDLE, RD_ACTIVE , RD_ACTIVE, RD_ACTIVE   		// PWLR=TRDL=150ns
#define write8(d) 		{ write_8(d); WRITE_DELAY; WR_STROBE; } 			// STROBEs are defined later
#define write16(x)    	{ uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst) 	{ RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; } // read 250ns after RD_ACTIVE goes low
#define READ_16(dst) 	{ uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define CTL_INIT()   	{ RD_OUTPUT; WR_OUTPUT; CD_OUTPUT; CS_OUTPUT; RESET_OUTPUT; }
#define WriteCmd(x)  	{ CD_COMMAND; write16(x); }
#define WriteData(x) 	{ CD_DATA; write16(x); }

void TFT_init_ports(void);

#endif /* _BOARD_H_ */

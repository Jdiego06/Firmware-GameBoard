/* Initialize debug console. */
#include "TFT_config.h"
void TFT_init_ports()
{
	/*TFT PORTS*/
	// enable all clock ports
	SIM->SCGC5 |= 	SIM_SCGC5_PORTA_MASK | \
					SIM_SCGC5_PORTB_MASK | \
					SIM_SCGC5_PORTC_MASK | \
					SIM_SCGC5_PORTE_MASK ;

	// Configuracion de pines como GPIO
	LCD_DO_PCR   = PORT_PCR_MUX(1);
	LCD_D1_PCR   = PORT_PCR_MUX(1);
	LCD_D2_PCR   = PORT_PCR_MUX(1);
	LCD_D3_PCR   = PORT_PCR_MUX(1);
	LCD_D4_PCR   = PORT_PCR_MUX(1);
	LCD_D5_PCR   = PORT_PCR_MUX(1);
	LCD_D6_PCR   = PORT_PCR_MUX(1);
	LCD_D7_PCR   = PORT_PCR_MUX(1);

	LCD_RD_PCR   = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	LCD_WR_PCR   = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	LCD_RS_PCR   = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	LCD_CS_PCR   = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	LCD_RST_PCR  = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;

	LCD_D0_Out();
	LCD_D1_Out();
	LCD_D2_Out();
	LCD_D3_Out();
	LCD_D4_Out();
	LCD_D5_Out();
	LCD_D6_Out();
	LCD_D7_Out();

	LCD_RD_Out();
	LCD_WR_Out();
	LCD_RS_Out();
	LCD_CS_Out();
	LCD_RST_Out();
	LCD_RST_Set();
}

inline void write8inline(uint8_t d) {
	  LCD_D0_W=(d&0x01)>>0;
	  LCD_D1_W=(d&0x02)>>1;
	  LCD_D2_W=(d&0x04)>>2;
	  LCD_D3_W=(d&0x08)>>3;
	  LCD_D4_W=(d&0x10)>>4;
	  LCD_D5_W=(d&0x20)>>5;
	  LCD_D6_W=(d&0x40)>>6;
	  LCD_D7_W=(d&0x80)>>7;
	  WR_STROBE;
  }

inline uint8_t read8inline(void) {
	uint8_t d=0;
	RD_ACTIVE;
	   d=(LCD_D0_R<<0)|(LCD_D1_R<<1)|(LCD_D2_R<<2)|(LCD_D3_R<<3)|(LCD_D4_R<<4)|(LCD_D5_R<<5)|(LCD_D6_R<<6)|(LCD_D7_R<<7);
	RD_IDLE;
	return d;
}

inline void setWriteDirInline(void){
	  LCD_D0_Out();
	  LCD_D1_Out();
	  LCD_D2_Out();
	  LCD_D3_Out();
	  LCD_D4_Out();
	  LCD_D5_Out();
	  LCD_D6_Out();
	  LCD_D7_Out();
}

inline void setReadDirInline(void){
	  LCD_D0_In();
	  LCD_D1_In();
	  LCD_D2_In();
	  LCD_D3_In();
	  LCD_D4_In();
	  LCD_D5_In();
	  LCD_D6_In();
	  LCD_D7_In();
}


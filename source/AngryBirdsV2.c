/*---------------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <jd99@outlook.com>, <cristian.osorio7365@uco.net.co> written this file.
 * As long as you retain this notice you can do whatever you want with this
 * stuff. If we meet some day, and you think this stuff is worth it, you can
 * buy me a beer in return. Poul-Henning Kamp
 * --------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------
 * Ing: Juan Diego Cardona
 * Ing: Cristian Camilo Osorio
 * Company: UCO
 * Date: 18-05-2019
 * Project: Angry Birds
 * Description:
 * 				Main code, this calls game_fsm every time there is a PIT interruption.
 * --------------------------------------------------------------------------------------*/
 
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "../drivers/custom/TFT/images/images.h"
#include "../drivers/custom/TFT/Adafruit_GFX.h"
#include "../drivers/custom/JOYSTICK/JOYSTICK.h"
#include "../drivers/custom/HAPTIC/BUTTON.h"
#include "game/game_fsm.h"


int main(void) {
	uint16_t ret;
    JOYSTICK_init();
    BUTTON_Init();
	MCUFRIEND_kbv_init();
	ret=MCUFRIEND_kbv_readID();
	MCUFRIEND_kbv_begin(ret);
	BOARD_InitBootClocks();

while(1){
	if (PIT_TIM_FLAG==1){
		PIT_TIM_FLAG=0;
		game_fsm();
	}
	__asm("wfi");
}
return 0 ;
}

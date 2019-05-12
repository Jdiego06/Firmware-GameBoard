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
	//raise clock to 120MHz
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

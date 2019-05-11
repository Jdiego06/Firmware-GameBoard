
/*----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <lecheverri@uco.edu.co> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 * Ing: Luis Felipe Echeverri
 * Company: UCO
 * Date: 27-04-2019
 * Project: Bomber Man
 * Description: This code implements detection of BTNA and BTNB of game board
 * 				Additionally, this driver enable the haptic feedback during
 * 				HAPTIC_TICKS time defined in the BUTTON.h file
 * ----------------------------------------------------------------------------*/

#include "BUTTON.h"
static uint8_t time_HAPTICflag=0;

void BUTTON_Init(void){
	 port_pin_config_t config_Button = {
	       kPORT_PullDisable,
	       kPORT_FastSlewRate,
	       kPORT_PassiveFilterDisable,
	       kPORT_OpenDrainDisable,
	       kPORT_LowDriveStrength,
	       kPORT_MuxAsGpio,
		   kPORT_UnlockRegister,
	  };
	 gpio_pin_config_t GPIO_config_Haptic={
		 kGPIO_DigitalOutput,
		 0,
	 };
	 gpio_pin_config_t GPIO_config_BTN={
		 kGPIO_DigitalInput,
		 0,
	 };

	 lptmr_config_t LPTMR_config;

	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_Lptmr0);

	PORT_SetPinConfig(BOARD_BTNA_PORT, BOARD_BTNA_PIN, &config_Button);
	PORT_SetPinConfig(BOARD_BTNB_PORT, BOARD_BTNB_PIN, &config_Button);
	PORT_SetPinConfig(BOARD_HAPTIC_PORT, BOARD_HAPTIC_PIN, &config_Button);

	PORT_SetPinInterruptConfig(BOARD_BTNA_PORT, BOARD_BTNA_PIN, kPORT_InterruptRisingEdge);
	PORT_SetPinInterruptConfig(BOARD_BTNB_PORT, BOARD_BTNB_PIN, kPORT_InterruptRisingEdge);

	GPIO_PinInit(BOARD_HAPTIC_GPIO, BOARD_HAPTIC_PIN, &GPIO_config_Haptic);
	GPIO_PinInit(BOARD_BTNB_GPIO, BOARD_BTNB_PIN, &GPIO_config_BTN);
	GPIO_PinInit(BOARD_BTNA_GPIO, BOARD_BTNA_PIN, &GPIO_config_BTN);
//
	NVIC_ClearPendingIRQ(BOARD_BTNA_IRQn);
	NVIC_EnableIRQ(BOARD_BTNA_IRQn);

#if(BOARD_BTNA_IRQn!=BOARD_BTNB_IRQn)
	NVIC_ClearPendingIRQ(BOARD_BTNB_IRQn);
	NVIC_EnableIRQ(BOARD_BTNB_IRQn);
#endif
	LPTMR_GetDefaultConfig(&LPTMR_config);
	LPTMR_Init(LPTMR0, &LPTMR_config);
	LPTMR_SetTimerPeriod(LPTMR0, DEBOUNCE_TICKS);
	LPTMR_EnableInterrupts(LPTMR0,1<<6);
	NVIC_ClearPendingIRQ(LPTMR0_IRQn);
	NVIC_EnableIRQ(LPTMR0_IRQn);
}


void BOARD_BTNA_IRQHandler(void){
	GPIO_PortClearInterruptFlags(BOARD_BTNA_GPIO, 1<<BOARD_BTNA_PIN);
	#if(BOARD_BTNA_IRQHandler==BOARD_BTNB_IRQHandler)
		GPIO_PortClearInterruptFlags(BOARD_BTNB_GPIO, 1<<BOARD_BTNB_PIN);
	#endif
	LPTMR_StopTimer(LPTMR0);
	time_HAPTICflag=0;
	LPTMR_SetTimerPeriod(LPTMR0, DEBOUNCE_TICKS);
	LPTMR_StartTimer(LPTMR0);
}

#if(BOARD_BTNA_IRQHandler!=BOARD_BTNB_IRQHandler)
void BOARD_BTNB_IRQHandler(void){
//incomplete function, please insert the code here if IRQn is diferent
}
#endif

void LPTMR0_IRQHandler(void){
	LPTMR_ClearStatusFlags(LPTMR0, 1<<7);
	if(time_HAPTICflag==0){
		if(GPIO_PinRead(BOARD_BTNA_GPIO, BOARD_BTNA_PIN)==BOARD_BTNA_PRESSED){
			BTNA_FLAG=1;
		}
		if(GPIO_PinRead(BOARD_BTNB_GPIO, BOARD_BTNB_PIN)==BOARD_BTNB_PRESSED){
			BTNB_FLAG=1;
		}
		LPTMR_SetTimerPeriod(LPTMR0, HAPTIC_TICKS);
		GPIO_PortSet(BOARD_HAPTIC_GPIO, 1<<BOARD_HAPTIC_PIN);
		time_HAPTICflag=1;
	}else{
		LPTMR_StopTimer(LPTMR0);
		LPTMR_SetTimerPeriod(LPTMR0, DEBOUNCE_TICKS);
		GPIO_PortClear(BOARD_HAPTIC_GPIO, 1<<BOARD_HAPTIC_PIN);
		time_HAPTICflag=0;
	}
}



/*----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <lecheverri@uco.edu.co> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------*/
/* Ing: Luis Felipe Echeverri
 * Company: UCO
 * Date: 27-04-2019
 * Project: Bomber Man
 * Description:	PIT and ADC configuration for read JOYSTICK position with minimum
 * 				CPU process
 * Note:        none
 * Revision     name          |date        | Observation
 *              Luis Felipe   |27-04-2019  | Change LPTMR for PIT because the LPTMR
 *              			  |            | is used for button debounce
 * ----------------------------------------------------------------------------*/

#include "JOYSTICK.h"
#include "fsl_pit.h"

uint16_t adc16_data;
adc16_channel_config_t JOYSTICK_ChannelConfigStruct;
volatile joystick_direction joystick_dir = joystick_middle;
volatile Joystic_Struct joystic;

//volatile joystic_data joysticData

void JOYSTICK_init(void) {
	/***************************************************
	 * Creates  PIT and ADC struct for configure it
	 ****************************************************/
	pit_config_t PIT_ConfigStruct;

	adc16_config_t JOYSTICK_configStruct;
	/***************************************************
	 *Init struct for config thresholds in joystick
	 ****************************************************/
	adc16_hardware_compare_config_t adc16HardwareCompareStruct = {
			kADC16_HardwareCompareMode3,
			GAME_BOARD_JOYSTICK_LOWER_ADC_LIMIT,
			GAME_BOARD_JOYSTICK_UPPER_ADC_LIMIT };

	/********************************************************************************
	 *  ADC Config Steps (comments are used only for class explain purpose)
	 *  Step 1  - Enable ADC1 clock
	 *  Step 2  - Get default ADC config
	 *  Step 3  - Disable AsynchronousClock,
	 *  		  Set bus clock as clock source for ADC
	 *  		  Divider it by 2
	 *  		  Set 16 bit ADC resolution
	 *  		  And Disable ContinuousConversion
	 *  Step 4  - Apply the previous configuration
	 *  Step 5  - Enable Hardware trigger for init ADC conversion
	 *  Step 6  - AutoCalibrate of ADC1 system
	 *  Step 7  - Set hardware compare for detect when the ADC
	 *  		  value is less than the GAME_BOARD_JOYSTICK_LOWER_ADC_LIMIT or
	 *  		  grater than GAME_BOARD_JOYSTICK_UPPER_ADC_LIMIT an only
	 *  		  will generate interrupt when is out of this range
	 *  Step 8  - Set init convert channel (I will choose GAME_BOARD_JOYSTICK_CHANNEL_X)
	 *  	   	  but no matter what channel you choose for start if X or Y.
	 *  Step 9  - Enable ADC interrupt when COCO is set. Remember that, when
	 *  		  hardware compare is enable, COCO is set upon completion of a
	 *  		  conversion only if the compare result is true.
	 *  Step 10 - Set Single-ended conversions
	 *  Step 11 - Apply the previous channel configuration
	 *  Step 12 - Set The PIT as hardware trigger for ADC1 in SIM->SOPT7
	 *
	 ********************************************************************************/
	CLOCK_EnableClock(GAME_BOARD_JOYSTICK_ADC_CLOCK);
	ADC16_GetDefaultConfig(&JOYSTICK_configStruct);

	JOYSTICK_configStruct.enableAsynchronousClock = false;
	JOYSTICK_configStruct.clockSource = kADC16_ClockSourceAlt0;
	JOYSTICK_configStruct.clockDivider = kADC16_ClockDivider2;
	JOYSTICK_configStruct.resolution = kADC16_ResolutionSE16Bit;
	JOYSTICK_configStruct.enableContinuousConversion = false;

	ADC16_Init(GAME_BOARD_JOYSTICK_ADC_BASE, &JOYSTICK_configStruct);

	ADC16_EnableHardwareTrigger(GAME_BOARD_JOYSTICK_ADC_BASE, true);
	ADC16_DoAutoCalibration(GAME_BOARD_JOYSTICK_ADC_BASE);
	ADC16_SetHardwareCompareConfig(GAME_BOARD_JOYSTICK_ADC_BASE,
			&adc16HardwareCompareStruct);

	JOYSTICK_ChannelConfigStruct.channelNumber = GAME_BOARD_JOYSTICK_CHANNEL_X;
	JOYSTICK_ChannelConfigStruct.enableInterruptOnConversionCompleted = true;
	JOYSTICK_ChannelConfigStruct.enableDifferentialConversion = false;

	ADC16_SetChannelConfig( GAME_BOARD_JOYSTICK_ADC_BASE,
	GAME_BOARD_JOYSTICK_ADC_CHANNEL_GROUP, &JOYSTICK_ChannelConfigStruct);
	/*SELECT PIT AS HW TRIGER FOR ADC1 */
	SIM->SOPT7 |= 0x8400U;

	/********************************************************************************
	 * PIT for ADC HW trigger Config
	 *********************************************************************************
	 * Step 1 - Enable PIT clock
	 * Step 2 - Load Default config
	 * Step 3 - enable Pit operation in debug mode
	 * Step 4 - Apply the previous configuration
	 * Step 5 - Set PIT interrupt period to 20ms approximately
	 * Step 6 - Enable interrupt in PIT module
	 * Step 7 - Start PIT
	 * Step 8 - Enable PIT interrupt in NVIC
	 * Step 9 - Enable ADC interrupt in NVIC
	 ********************************************************************************/
	CLOCK_EnableClock(kCLOCK_Pit0);
	PIT_GetDefaultConfig(&PIT_ConfigStruct);
	PIT_ConfigStruct.enableRunInDebug = true;
	PIT_Init(PIT, &PIT_ConfigStruct);
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, 1200000);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, PIT_TCTRL_TIE_MASK);
	PIT_StartTimer(PIT, kPIT_Chnl_0);

	//Enable ADC interrupt
	EnableIRQ(PIT0_IRQn);
	EnableIRQ(GAME_BOARD_JOYSTICK_ADC_IRQn);
}

/********************************************************************************
 * ADC1 ISR, this interrupt only take place when the JOYSTICK is not stay in middle
 * position
 ********************************************************************************/
void GAME_BOARD_JOYSTICK_ADC_IRQ_HANDLER_FUNC(void) {
	GAME_BOARD_JOYSTICK_ADC_BASE->R[0];

	adc16_data = ADC16_GetChannelConversionValue( GAME_BOARD_JOYSTICK_ADC_BASE,
	GAME_BOARD_JOYSTICK_ADC_CHANNEL_GROUP);

	if (JOYSTICK_ChannelConfigStruct.channelNumber
			== GAME_BOARD_JOYSTICK_CHANNEL_X) {
		if (adc16_data <= GAME_BOARD_JOYSTICK_LOWER_ADC_LIMIT) {
			joystick_dir = joystick_right;
		} else {
			joystick_dir = joystick_left;
		}
		joystic.Ypos = adc16_data;
	} else {
		if (adc16_data <= GAME_BOARD_JOYSTICK_LOWER_ADC_LIMIT) {
			joystick_dir = joystick_up;
		} else {
			joystick_dir = joystick_down;
		}
		joystic.Xpos = adc16_data;
	}
	JOYSTICK_FLAG = 1;
	__DSB();
}

/********************************************************************
 * PIT0 ISR: In this function the interrupt is acknowledge an after it
 * 			the channel to convert is toogle from X to Y and vice versa
 *
 ********************************************************************/

void PIT0_IRQHandler(void) {
	/********************************************************************
	 * Interrupt acknowledgment, clear TCF bit in CSR Register
	 ********************************************************************/
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);
	/********************************************************************
	 * toggle ADC channel
	 ********************************************************************/

	if (JOYSTICK_ChannelConfigStruct.channelNumber
			== GAME_BOARD_JOYSTICK_CHANNEL_X) {
		JOYSTICK_ChannelConfigStruct.channelNumber =
				GAME_BOARD_JOYSTICK_CHANNEL_Y;
	} else {
		JOYSTICK_ChannelConfigStruct.channelNumber =
				GAME_BOARD_JOYSTICK_CHANNEL_X;
	}
	ADC16_SetChannelConfig( GAME_BOARD_JOYSTICK_ADC_BASE,
	GAME_BOARD_JOYSTICK_ADC_CHANNEL_GROUP, &JOYSTICK_ChannelConfigStruct);
	PIT_TIM_FLAG = 1;
	__DSB();
}

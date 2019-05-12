
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
 * Description:
 * ----------------------------------------------------------------------------*/

#ifndef CUSTOM_JOYSTICK_H_
#define CUSTOM_JOYSTICK_H_
#include "../GLOBAL.h"
#include "fsl_adc16.h"

#define ADC16_FULL_RANGE 							65535 //16 bits
//#define GAME_BOARD_JOYSTICK_UPPER_ADC_LIMIT 		(int)((float)(ADC16_FULL_RANGE)*(0.7))
//#define GAME_BOARD_JOYSTICK_LOWER_ADC_LIMIT 		(int)((float)(ADC16_FULL_RANGE)*(0.3))

#define GAME_BOARD_JOYSTICK_UPPER_ADC_LIMIT 		(int)((float)(ADC16_FULL_RANGE)*(1))
#define GAME_BOARD_JOYSTICK_LOWER_ADC_LIMIT 		(int)((float)(ADC16_FULL_RANGE)*(0))


#define GAME_BOARD_JOYSTICK_ADC_BASE ADC1
#define GAME_BOARD_JOYSTICK_ADC_CHANNEL_GROUP 		0U //GROUP A
#define GAME_BOARD_JOYSTICK_CHANNEL_Y 				19  //ADC1_DM0-ADC0_DM3 // pin 21 MK64F // 10011 AD19 para el ADC1 pag 127
#define GAME_BOARD_JOYSTICK_CHANNEL_X 				0	//ADC1_DP0-ADC0_DP3 // pin 20 MK64F // 00000 DAD0 para el ADC1 pag 126
#define GAME_BOARD_JOYSTICK_ADC_CLOCK				kCLOCK_Adc1
#define GAME_BOARD_JOYSTICK_ADC_IRQn 				ADC1_IRQn
#define GAME_BOARD_JOYSTICK_ADC_IRQ_HANDLER_FUNC 	ADC1_IRQHandler

typedef enum{
	joystick_middle,
	joystick_up,
	joystick_down,
	joystick_right,
	joystick_left,
}joystick_direction;


typedef struct Joystic_Struc{
	int Xpos;
	int Ypos;
}Joystic_Struct;


extern volatile Joystic_Struct joystick;
extern volatile joystick_direction joystick_dir;

void JOYSTICK_init(void);
#endif /* CUSTOM_JOYSTICK_H_ */

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
 * Description: this code define the interrupt flag used
 * ----------------------------------------------------------------------------*/


#ifndef CUSTOM_GLOBAL_H_
#define CUSTOM_GLOBAL_H_
#include "stdint.h"
#include "GLOBAL.h"
typedef union{
	uint32_t flag;
	struct {
		uint32_t BTNA 		: 1;
		uint32_t BTNB		: 1;
		uint32_t LPTMR		: 1;
		uint32_t JOYSTICK	: 1;
		uint32_t PIT_TIM	: 1;
	}bits;
}interrupt_flag;

extern interrupt_flag _interrupt_flag;

#define INT_FLAG _interrupt_flag.flag
#define BTNA_FLAG _interrupt_flag.bits.BTNA
#define BTNB_FLAG _interrupt_flag.bits.BTNB
#define LPTMR_FLAG _interrupt_flag.bits.LPTMR
#define JOYSTICK_FLAG _interrupt_flag.bits.JOYSTICK
#define PIT_TIM_FLAG _interrupt_flag.bits.PIT_TIM

#endif /* CUSTOM_GLOBAL_H_ */

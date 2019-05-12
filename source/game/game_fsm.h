/*----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <jd99@outlook.com> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 * Ing: Juan Diego Cardona Marín
 * Ing: Cristian Camilo Osorio Rodriguez
 * Company: UCO
 * Date: 09-05-2019
 * Project: Angry Birds
* ----------------------------------------------------------------------------*/

#ifndef GAME_FSM_H_
#define GAME_FSM_H_


#include "../drivers/custom/TFT/images/images.h"
#include "../drivers/custom/TFT/MCUFRIEND_kbv.h"
#include "../drivers/custom/JOYSTICK/JOYSTICK.h"





typedef enum {
	init,
	waitingforstart,
	painting_map,
	pause,
	gaming,
	gameover,
}game_states;

void game_fsm(void);
#endif /* GAME_FSM_H_ */

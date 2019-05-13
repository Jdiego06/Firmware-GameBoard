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


#include "JOYSTICK/JOYSTICK.h"
#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"


#include "utilities.h"
#include "Adafruit_GFX.h"
#include "fix_shot_fsm.h"
#include "shot_bird_fsm.h"


#define TailWidth 	16
#define TailHeight  16

//Max Values of bird positions
#define MaxX 30
#define MaxY 110
#define MinY 40


#define TILE_W 16
#define TILE_H 16
#define SPANX 32
#define SPANY 32

extern uint16_t actual_sprint_buffer[(TILE_W + (2 * SPANX))
		* ((2 * SPANY) + (2 * TILE_H))]; //define size according to maximum convert image


typedef enum {
	init,
	waitingforstart,
	painting_map,
	pause,
	gaming,
	shot_bird,
	gameover,
}game_states;

void game_fsm(void);
#endif

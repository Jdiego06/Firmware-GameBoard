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
#include  "paint_map_fsm.h"
#include "paint_dust_fsm.h"

#include <stdio.h>
#include <stdbool.h>

#define TailWidth 	16
#define TailHeight  16


//Max Values of bird positions
#define MaxX 35
#define MaxY 110
#define MinY 40 //Before 40-75


//Choose the bird
#define Bird BirdOne


#define INIT_SHOTS 3

//Define tiles size
#define TILE_W 16
#define TILE_H 16
#define SPANX 16
#define SPANY 16



extern uint16_t actual_sprint_buffer[(TILE_W + (2 * SPANX))
		* ((2 * SPANY) + (2 * TILE_H))]; //define size according to maximum convert image


extern int remaining_shots;
extern int coorDustx; //Coors of pig that will be killed
extern int coorDusty; //Coors of pig that will be killed
extern int PigToKill;
extern int BlockToDestroy;
extern bool killPig;
extern bool destroyBlock;
//extern uint16_t *Bird;

typedef enum {
	init,
	waitingforstart,
	painting_map,
	gaming,
	draw_dust,
	shot_bird,
	gameover,
}game_states;

void game_fsm(void);
#endif

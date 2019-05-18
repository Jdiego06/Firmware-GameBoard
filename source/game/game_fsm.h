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
 * --------------------------------------------------------------------------------------*/

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


#define Bird BirdOne
#define INIT_SHOTS 4

/*    Tiles sizes    */
#define TILE_WIDHT 16
#define TILE_HEIGHT 16
#define SPANX 16
#define SPANY 16


/*    Define size of buffer according to maximum convert image    */
extern uint16_t actual_sprint_buffer[(TILE_WIDHT + (2 * SPANX))*((2 * SPANY) + (2 * TILE_HEIGHT))];


extern int remaining_shots;
extern int coorDustx;
extern int coorDusty;
extern int PigToKill;
extern int BlockToDestroy;
extern bool killPig;
extern bool destroyBlock;


/*    States of the game    */
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

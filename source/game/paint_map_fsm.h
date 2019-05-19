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

#ifndef PAINT_MAP_FSM_H
#define PAINT_MAP_FSM_H

#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"
#include "fsl_pit.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"
#include "game_fsm.h"

extern int matrix_pigs[10][2];
extern int matrix_blocks[10][2];
extern unsigned short *Background;
extern unsigned short *Bird;

void paint_caratule(void);

void select_world(int map);
void select_bird(int world);
void select_background(int world);

void paint_pigs(void);
void paint_blocks(void);
void paint_lifes(void);
void paint_background(void);

void matris_copy(void * destmat, void * srcmat, int size);
int pseudo_random(uint8_t range);

#endif


#ifndef PAINT_MAP_FSM_H
#define PAINT_MAP_FSM_H

#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"
#include "game_fsm.h"

extern int matrix_pigs[3][2];

void paint_pigs(void);
void paintMap(void);
void paint_lifes(void);

#endif


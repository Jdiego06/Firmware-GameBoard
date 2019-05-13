#ifndef SHOT_BIRD_FSM_H
#define SHOT_BIRD_FSM_H

#include "JOYSTICK/JOYSTICK.h"
#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"
#include "fix_shot_fsm.h"


#define gravity 8.2
#define CteVix 	1.23
#define y0		0
#define x0		0


void shot_bird_fsm(void);

#endif

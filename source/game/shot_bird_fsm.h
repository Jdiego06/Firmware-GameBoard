#ifndef SHOT_BIRD_FSM_H
#define SHOT_BIRD_FSM_H

#include "JOYSTICK/JOYSTICK.h"
#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"
#include "fix_shot_fsm.h"

#define duracionVuelo 0.5   // inversamente Proporcional max 1.2 min ?
#define velocity 4
#define gravity 5.2
#define y0		0
#define x0		0


void shot_bird_fsm(void);

#endif

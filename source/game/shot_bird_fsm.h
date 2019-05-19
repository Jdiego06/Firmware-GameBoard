/*---------------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <jd99@outlook.com>, <cristian.osorio7365@uco.net.co> wrote this file.
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


#ifndef SHOT_BIRD_FSM_H
#define SHOT_BIRD_FSM_H

#include "JOYSTICK/JOYSTICK.h"
#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"
#include "fix_shot_fsm.h"
#include "paint_map_fsm.h"

#include <stdbool.h>

/*---------------------------------------------------------------------------------------
 *								physical constants of the world
 * --------------------------------------------------------------------------------------*/
#define DISTANCE_FLIGHT 0.5
#define VELOCITY 1
#define GRAVITY 5


int shot_bird_fsm(void);

#endif

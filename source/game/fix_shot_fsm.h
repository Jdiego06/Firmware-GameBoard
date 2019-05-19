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

#ifndef FIX_SHOT_FSM
#define FIX_SHOT_FSM

#include "JOYSTICK/JOYSTICK.h"
#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"

/*    Range of bird positions (in px)    */
#define MAX_X 35
#define MAX_Y 110
#define MinY 40
#define INIT_X_VALUE 35
#define INIT_Y_VALUE 75

extern int16_t last_x_position;
extern int16_t last_y_position;
extern int16_t left_span;
extern int16_t rigth_span;
extern int16_t up_span;
extern int16_t down_span;
extern int joystick_x_value;
extern int joystick_y_value;

extern void fix_shot_fsm(void);
extern void calculate_span(int16_t x, int16_t y);

#endif

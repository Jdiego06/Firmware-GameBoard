#ifndef FIX_SHOT_FSM
#define FIX_SHOT_FSM

#include "../../drivers/custom/JOYSTICK/JOYSTICK.h"
#include "../drivers/custom/TFT/images/images.h"
#include "../drivers/custom/TFT/MCUFRIEND_kbv.h"
#include "../drivers/custom/JOYSTICK/JOYSTICK.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"


#define TILE_W 16
#define TILE_H 16
#define SPANX 32
#define SPANY 70

#define MaxX 30
#define MaxY 110
#define MinY 40

void fix_shot_fsm(void);
void CalculateSpan(int16_t x, int16_t y);

#endif

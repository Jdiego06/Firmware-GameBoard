#ifndef FIX_SHOT_FSM
#define FIX_SHOT_FSM

#include "JOYSTICK/JOYSTICK.h"
#include "TFT/images/images.h"
#include "TFT/MCUFRIEND_kbv.h"
#include  "Adafruit_GFX.h"
#include  "utilities.h"


extern int16_t LastX;
extern int16_t LastY;

extern int16_t left_span;
extern int16_t rigth_span;
extern int16_t up_span;
extern int16_t down_span;


void fix_shot_fsm(void);
extern void CalculateSpan(int16_t x, int16_t y);



#endif

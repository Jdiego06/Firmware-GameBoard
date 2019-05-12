#include "fix_shot_fsm.h"

uint16_t actual_sprint_buffer2[(TILE_W + (2 * SPANX))
		* ((2 * SPANY) + (2 * TILE_H))]; //define size according to maximum convert image

int16_t LastX = 35;
int16_t LastY = 75;

int16_t left_span;
int16_t rigth_span;
int16_t up_span;
int16_t down_span;

void fix_shot_fsm(void) {

	if (JOYSTICK_FLAG == 1) {
		JOYSTICK_FLAG = 0;

		//Get Joystick Values
		int JoysticValueX = (joystick.Xpos / 1000) * 1.79 - 23.84;
		int JoysticValueY = (joystick.Ypos / 1000) * 1.52 + 24.74;

		//Adjust Joystick Values between Max and Min
		if (JoysticValueX > MaxX) {
			JoysticValueX = MaxX;
		}

		if (JoysticValueY > MaxY) {
			JoysticValueY = MaxY;
		}

		if (JoysticValueY < MinY) {
			JoysticValueY = MinY;
		}

		//int JoysticValueY=joystic.Ypos;

		/*char str[20];
		 sprintf(str, "%d", JoysticValueY);
		 printf(str);
		 printf("\n\n");
		 */

		//MCUFRIEND_kbv_print_tail(&Background[(320 * 40)], 0, 40, 320, 80);
		CalculateSpan(JoysticValueX, JoysticValueY);

		imagesoverlay((unsigned short *) &BirdOne,
				(unsigned short *) &Background,
				(unsigned short *) &actual_sprint_buffer2, 320,
				JoysticValueX, JoysticValueY, left_span,
				rigth_span, up_span, down_span, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail((unsigned short *) &actual_sprint_buffer2,
				JoysticValueX - left_span, JoysticValueY- up_span, 16 + rigth_span + left_span,
				16 + up_span + down_span);

	}

}

void CalculateSpan(int16_t x, int16_t y) {

	if ((LastX - x) > 0) {
		left_span = 0;
		rigth_span = (LastX - x);
	} else {
		left_span = (x - LastX);
		rigth_span = 0;
	}

	if ((LastY - y) > 0) {
		up_span = 0;
		down_span = (LastY - y);
	} else {
		up_span = (y - LastY);
		down_span = 0;
	}
	LastX = x;
	LastY = y;
}


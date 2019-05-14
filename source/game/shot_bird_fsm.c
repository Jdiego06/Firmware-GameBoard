#include "shot_bird_fsm.h"
#include <stdlib.h>
#include <stdbool.h>
#include "game_fsm.h"
#include <math.h>

double Time = 0;
double NextYposition = 0;
double NextXposition = 0;
double Ypos=0;
double Xpos=0;
double Counter = 0;

void shot_bird_fsm(void) {

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

	Ypos = JoysticValueY - 75;
	Xpos = JoysticValueX;
	NextXposition = Xpos - 4;

	Counter = 0;
	while (true) {

		Time = Counter * (duracionVuelo*Xpos+7)/ 75;

		NextYposition = (
				y0+ Ypos * Time * (abs(Ypos) / sqrt(pow(Xpos, 2) + pow(Ypos, 2)))
				- (0.5) * gravity * (pow(Time, 2)));

		NextYposition = (int16_t) (JoysticValueY - NextYposition);

		if (NextYposition > 190) {
			return;
		}

		if (NextYposition < 0) {
			return;
		}

		NextXposition = (int16_t) (NextXposition + 4);


		if (NextXposition > 304) {
			return;
		}

		if (NextXposition < 0) {
			return;
		}

		CalculateSpan(NextXposition, NextYposition);

		imagesoverlay((unsigned short *) &Bird,
				(unsigned short *) &Background,
				(unsigned short *) &actual_sprint_buffer, 320, NextXposition,
				NextYposition, left_span, rigth_span, up_span, down_span, 16,
				16, 0Xffff);

		MCUFRIEND_kbv_print_tail((unsigned short *) &actual_sprint_buffer,
				(NextXposition - left_span), (NextYposition - up_span),
				(TailWidth + rigth_span + left_span),
				(TailHeight + up_span + down_span));

		Counter++;

		for (int var = 0; var < 145000 * velocity; ++var) {
			__asm("nop");
		}

	}
}


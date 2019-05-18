#include "shot_bird_fsm.h"
#include "paint_map_fsm.h"
#include <stdlib.h>
#include <stdbool.h>
#include "game_fsm.h"
#include <math.h>

double Time = 0;
double NextYposition = 0;
double NextXposition = 0;
double Ypos = 0;
double Xpos = 0;
double Counter = 0;

int shot_bird_fsm(void) {
	killPig = false;
	destroyBlock = false;


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
	bool RetFlag=false;


	while (true) {

		Time = Counter * (duracionVuelo * Xpos + 7) / 75;

		NextYposition = (
		y0 + Ypos * Time * (abs(Ypos) / sqrt(pow(Xpos, 2) + pow(Ypos, 2)))
				- (0.5) * gravity * (pow(Time, 2)));

		//Calcula las posiciones
		NextYposition = (int16_t) (JoysticValueY - NextYposition);
		NextXposition = (int16_t) (NextXposition + 4);

		//Calcula si el pajaro sale de la pantalla

		if (NextYposition > (240 - TILE_H)) {
			NextYposition = (240 - TILE_H);
			coorDustx = NextXposition;
			coorDusty = NextYposition;
			RetFlag = true;
		}

		if (NextXposition >= (320 - TILE_W)) {
			NextXposition = (320 - TILE_W);
			coorDustx = NextXposition;
			coorDusty = NextYposition;
			RetFlag = true;
		}

		//mira si el pajaro choca contra un objeto

		for (int i = 0; i < 3; i++) {

			int BlockX = matrix_blocks[i][0];
			int BlockY = matrix_blocks[i][1];

			int PigX = matrix_pigs[i][0];
			int PigY = matrix_pigs[i][1];

			if ((NextXposition >= (PigX - TILE_W)
					&& NextXposition <= (PigX + TILE_W))
					|| (NextXposition >= (BlockX - TILE_W)
							&& NextXposition <= (BlockX + TILE_W))) {

				//choque contra marrano

				if (NextYposition >= (PigY - TILE_H)
						&& NextYposition <= (PigY + TILE_H)) {

					NextXposition = PigX;
					NextYposition = PigY;

					coorDustx = PigX;
					coorDusty = PigY;

					PigToKill = i;
					destroyBlock = false;
					killPig = true;
					RetFlag = true;

					break;
				}
				//choque contra bloque
				if (NextYposition >= (BlockY - TailHeight)
						&& NextYposition <= (BlockY + TILE_H)) {

					NextXposition = BlockX;
					NextYposition = BlockY;

					coorDustx = BlockX;
					coorDusty = BlockY;

					BlockToDestroy = i;
					destroyBlock = true;
					killPig = false;
					RetFlag = true;
					break;
				}

			}

		}

		CalculateSpan(NextXposition, NextYposition);

		imagesoverlay((unsigned short *) &Bird, (unsigned short *) &Background,
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

		if (RetFlag == true) {
			return 0;
		}
	}
}


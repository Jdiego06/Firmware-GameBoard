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
 * Description:
 * 				This code implements a function capable of calculating
 * 				and changing a parabolic trajectory with the bird, according
 * 				to the initial values ​​of the joystick, besides that it is able
 * 				to verify if the bird hits against one of the pigs, one of
 * 				the blocks, or against the edge of the screen.
 * --------------------------------------------------------------------------------------*/

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

	/*---------------------------------------------------------------------------------------
	 *			Adjusts the position of the joystick to a new frame of reference.
	 * --------------------------------------------------------------------------------------*/
	Ypos = JoysticValueY - 75;
	Xpos = JoysticValueX;
	NextXposition = Xpos - 4;

	Counter = 0;
	bool RetFlag = false;

	while (true) {

		/*---------------------------------------------------------------------------------------
		 *			Calculate the following position values ​​in X and Y.
		 * --------------------------------------------------------------------------------------*/
		Time = Counter * (DISTANCE_FLIGHT * Xpos + 7) / 75;

		NextYposition = JoysticValueY - (Ypos * Time * (abs(Ypos) / sqrt(pow(Xpos, 2) + pow(Ypos, 2)))
						- (0.5) * GRAVITY * (pow(Time, 2)));

		NextXposition = (int16_t) (NextXposition + 4);




		/*---------------------------------------------------------------------------------------
		 *			Check if the next step, the bird hits the edge of the screen,
		 *			if so, the function adjusts the new position, and returns at
		 *			the end.
		 * --------------------------------------------------------------------------------------*/

		if (NextYposition > (240 - TILE_HEIGHT)) {
			NextYposition = (240 - TILE_HEIGHT);
			coorDustx = NextXposition;
			coorDusty = NextYposition;
			RetFlag = true;
		}

		if (NextXposition >= (320 - TILE_WIDHT)) {
			NextXposition = (320 - TILE_WIDHT);
			coorDustx = NextXposition;
			coorDusty = NextYposition;
			RetFlag = true;
		}

		/*---------------------------------------------------------------------------------------
		 *			Verify if in the next step, the bird collides with an object,
		 *			 if so, verify the type of object, and return at the end.
		 * --------------------------------------------------------------------------------------*/

		for (int i = 0; i < 3; i++) {

			int BlockX = matrix_blocks[i][0];
			int BlockY = matrix_blocks[i][1];

			int PigX = matrix_pigs[i][0];
			int PigY = matrix_pigs[i][1];

			if ((NextXposition >= (PigX - TILE_WIDHT)
					&& NextXposition <= (PigX + TILE_WIDHT))
					|| (NextXposition >= (BlockX - TILE_WIDHT)
							&& NextXposition <= (BlockX + TILE_WIDHT))) {

				/*    If the bird hits a pig    */
				if (NextYposition >= (PigY - TILE_HEIGHT)
						&& NextYposition <= (PigY + TILE_HEIGHT)) {

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
				/*    If the bird hits a block    */
				if (NextYposition >= (BlockY - TILE_HEIGHT)
						&& NextYposition <= (BlockY + TILE_HEIGHT)) {

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

		/*---------------------------------------------------------------------------------------
		 *			                       Paint the bird
		 * --------------------------------------------------------------------------------------*/
		CalculateSpan(NextXposition, NextYposition);

		imagesoverlay((unsigned short *) &Bird, (unsigned short *) &Background,
				(unsigned short *) &actual_sprint_buffer, 320, NextXposition,
				NextYposition, left_span, rigth_span, up_span, down_span, 16,
				16, 0Xffff);

		MCUFRIEND_kbv_print_tail((unsigned short *) &actual_sprint_buffer,
				(NextXposition - left_span), (NextYposition - up_span),
				(TILE_WIDHT + rigth_span + left_span),
				(TILE_HEIGHT + up_span + down_span));

		Counter++;


		/*---------------------------------------------------------------------------------------
		 *		        	returns if the bird hit an object or the screen
		 * --------------------------------------------------------------------------------------*/
		if (RetFlag == true) {
			return 0;
		}


		/*---------------------------------------------------------------------------------------
		*		        Wait a while until the next cycle, to give more or less speed :(
		* --------------------------------------------------------------------------------------*/
		for (int var = 0; var < 145000 * VELOCITY; ++var) {
			__asm("nop");
		}
	}
}


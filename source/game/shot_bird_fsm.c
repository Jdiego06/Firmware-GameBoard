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

double time = 0;
double next_x_position = 0;
double next_y_position = 0;
double actual_y_position = 0;
double actual_x_position = 0;
double counter = 0;

int shot_bird_fsm(void) {

	/*---------------------------------------------------------------------------------------
	 *			Adjusts the position of the joystick to a new frame of reference.
	 * --------------------------------------------------------------------------------------*/
	actual_y_position = joystick_y_value - 75;
	actual_x_position = joystick_x_value;
	next_x_position = actual_x_position - 4;

	counter = 0;
	bool return_flag = false;

	while (true) {

		/*---------------------------------------------------------------------------------------
		 *			Calculate the following position values ​​in X and Y.
		 * --------------------------------------------------------------------------------------*/
		time = counter * (DISTANCE_FLIGHT * actual_x_position + 7) / 75;

		next_y_position = joystick_y_value
						- (actual_y_position * time
						* (abs(actual_y_position)
						/ sqrt(pow(actual_x_position, 2)
						+ pow(actual_y_position, 2)))
						- (0.5) * GRAVITY * (pow(time, 2)));

		next_x_position = (int16_t) (next_x_position + 4);

		/*---------------------------------------------------------------------------------------
		 *			Check if the next step, the bird hits the edge of the screen,
		 *			if so, the function adjusts the new position, and returns at
		 *			the end.
		 * --------------------------------------------------------------------------------------*/

		if (next_y_position > (240 - TILE_HEIGHT)) {
			next_y_position = (240 - TILE_HEIGHT);
			coor_dusty_x = next_x_position;
			coor_dusty_y = next_y_position;
			return_flag = true;
		}

		if (next_x_position >= (320 - TILE_WIDHT)) {
			next_x_position = (320 - TILE_WIDHT);
			coor_dusty_x = next_x_position;
			coor_dusty_y = next_y_position;
			return_flag = true;
		}

		/*---------------------------------------------------------------------------------------
		 *			Verify if in the next step, the bird collides with an object,
		 *			 if so, verify the type of object, and return at the end.
		 * --------------------------------------------------------------------------------------*/

		for (int i = 0; i < (sizeof(matrix_pigs) / sizeof(matrix_pigs[0])); i++) {

			int BlockX = matrix_blocks[i][0];
			int BlockY = matrix_blocks[i][1];

			int PigX = matrix_pigs[i][0];
			int PigY = matrix_pigs[i][1];

			if ((next_x_position >= (PigX - TILE_WIDHT)
					&& next_x_position <= (PigX + TILE_WIDHT))
					|| (next_x_position >= (BlockX - TILE_WIDHT)
							&& next_x_position <= (BlockX + TILE_WIDHT))) {

				/*    If the bird hits a pig    */
				if (next_y_position >= (PigY - TILE_HEIGHT)
						&& next_y_position <= (PigY + TILE_HEIGHT)) {

					next_x_position = PigX;
					next_y_position = PigY;

					coor_dusty_x = PigX;
					coor_dusty_y = PigY;

					pig_to_kill = i;
					destroy_block = false;
					kill_pig = true;
					return_flag = true;

					break;
				}
				/*    If the bird hits a block    */
				if (next_y_position >= (BlockY - TILE_HEIGHT)
						&& next_y_position <= (BlockY + TILE_HEIGHT)) {

					next_x_position = BlockX;
					next_y_position = BlockY;

					coor_dusty_x = BlockX;
					coor_dusty_y = BlockY;

					block_to_destroy = i;
					destroy_block = true;
					kill_pig = false;
					return_flag = true;
					break;
				}

			}

		}

		/*---------------------------------------------------------------------------------------
		 *			                       Paint the bird
		 * --------------------------------------------------------------------------------------*/
		calculate_span(next_x_position, next_y_position);

		imagesoverlay(Bird, Background,
				(unsigned short *) &actual_sprint_buffer, 320, next_x_position,
				next_y_position, left_span, rigth_span, up_span, down_span, 16,
				16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer,
				(next_x_position - left_span), (next_y_position - up_span),
				(TILE_WIDHT + rigth_span + left_span),
				(TILE_HEIGHT + up_span + down_span));

		counter++;

		/*---------------------------------------------------------------------------------------
		 *		        	returns if the bird hit an object or the screen
		 * --------------------------------------------------------------------------------------*/
		if (return_flag == true) {
			return 0;
		}

		/*---------------------------------------------------------------------------------------
		 *		        Wait a while until the next cycle, to give more or less speed :(
		 * --------------------------------------------------------------------------------------*/
		for (double i = 0; i < 20000/VELOCITY; i++) {
			__asm("nop");
		}
	}
}


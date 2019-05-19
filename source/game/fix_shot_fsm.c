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
 * 				This code implements the necessary functionalities
 * 				to draw the position of a bird, given by the location
 * 				of the Joystic.
 * --------------------------------------------------------------------------------------*/

#include "fix_shot_fsm.h"
#include "game_fsm.h"

int16_t last_x_position;
int16_t last_y_position;

int16_t left_span;
int16_t rigth_span;
int16_t up_span;
int16_t down_span;

/*---------------------------------------------------------------------------------------
 *			This function reads the value of the joystic and adjusts
 *			it to a value in pixels given by the equations, the function
 *			prevents the positioning of the bird outside the range given
 *			by the cosntants: Xmax, Ymax, Ymin, Xmin. The function paints
 *			the bird in the corresponding position.
 * --------------------------------------------------------------------------------------*/

int joystick_x_value = INIT_X_VALUE;
int joystick_y_value = INIT_Y_VALUE;

void fix_shot_fsm(void) {

	if (JOYSTICK_FLAG == 1) {
		JOYSTICK_FLAG = 0;

		/*    Get the joystick values ​​and convert them to pixels    */
		joystick_x_value = (joystick.Xpos / 1000) * 1.79 - 23.84;
		joystick_y_value = (joystick.Ypos / 1000) * 1.52 + 24.74;

		/*    Adjust the values ​​if necessary    */
		if (joystick_x_value > MAX_X) {
			joystick_x_value = MAX_X;
		}

		if (joystick_y_value > MAX_Y) {
			joystick_y_value = MAX_Y;
		}

		if (joystick_y_value < MinY) {
			joystick_y_value = MinY;
		}

		/*    Paint the bird in TFT    */
		calculate_span(joystick_x_value, joystick_y_value);
		imagesoverlay(Bird, Background,
				(unsigned short *) &actual_sprint_buffer, 320, joystick_x_value,
				joystick_y_value, left_span, rigth_span, up_span, down_span, 16,
				16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer,
				(joystick_x_value - left_span), (joystick_y_value - up_span),
				(TILE_WIDHT + rigth_span + left_span),
				(TILE_HEIGHT + up_span + down_span));

	}

}

/*---------------------------------------------------------------------------------------
 *			This function allows to calculate the values ​​of span in all
 *			directions, given some current coordinates, and some previous
 *			coordinates.
 * --------------------------------------------------------------------------------------*/

void calculate_span(int16_t x, int16_t y) {

	if ((last_x_position - x) > 0) {
		left_span = 0;
		rigth_span = (last_x_position - x);
	} else {
		left_span = (x - last_x_position);
		rigth_span = 0;
	}

	if ((last_y_position - y) > 0) {
		up_span = 0;
		down_span = (last_y_position - y);
	} else {
		up_span = (y - last_y_position);
		down_span = 0;
	}
	last_x_position = x;
	last_y_position = y;
}


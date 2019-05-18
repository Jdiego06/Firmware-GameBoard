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

int16_t LastX;
int16_t LastY;

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

int JoysticValueX=INIT_X_VALUE;
int JoysticValueY=INIT_Y_VALUE;

void fix_shot_fsm(void) {

	if (JOYSTICK_FLAG == 1) {
		JOYSTICK_FLAG = 0;

		/*    Get the joystick values ​​and convert them to pixels    */
		JoysticValueX = (joystick.Xpos / 1000) * 1.79 - 23.84;
		JoysticValueY = (joystick.Ypos / 1000) * 1.52 + 24.74;


		/*    Adjust the values ​​if necessary    */
		if (JoysticValueX > MaxX) {
			JoysticValueX = MaxX;
		}

		if (JoysticValueY > MaxY) {
			JoysticValueY = MaxY;
		}

		if (JoysticValueY < MinY) {
			JoysticValueY = MinY;
		}


		/*    Paint the bird in TFT    */
		CalculateSpan(JoysticValueX, JoysticValueY);
		imagesoverlay((unsigned short *) &Bird, (unsigned short *) &Background,
				(unsigned short *) &actual_sprint_buffer, 320, JoysticValueX,
				JoysticValueY, left_span, rigth_span, up_span, down_span, 16,
				16, 0Xffff);

		MCUFRIEND_kbv_print_tail((unsigned short *) &actual_sprint_buffer,
				(JoysticValueX - left_span), (JoysticValueY - up_span),
				(TILE_WIDHT + rigth_span + left_span),
				(TILE_HEIGHT + up_span + down_span));

	}

}

/*---------------------------------------------------------------------------------------
 *			This function allows to calculate the values ​​of span in all
 *			directions, given some current coordinates, and some previous
 *			coordinates.
 * --------------------------------------------------------------------------------------*/

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


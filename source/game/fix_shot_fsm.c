#include "fix_shot_fsm.h"
#include "../drivers/custom/TFT/images/images.h"
#include "../drivers/custom/TFT/MCUFRIEND_kbv.h"
#include "../drivers/custom/JOYSTICK/JOYSTICK.h"
#include  "Adafruit_GFX.h"


#define TILE_W 16
#define TILE_H 16
#define SPANX 32
#define SPANY 32

uint16_t actual_sprint_buffer2[(TILE_W + (2 * SPANX))
		* ((2 * SPANY) + (2 * TILE_H))]; //define size according to maximum convert image


void fix_shot_fsm() {

	if (JOYSTICK_FLAG == 1) {
		JOYSTICK_FLAG = 0;

		int JoysticValueX = (joystic.Xpos / 1000) * 1.79 - 23.84;
		int JoysticValueY = (joystic.Ypos / 1000) * 1.52 + 24.74;
		//int JoysticValueY=joystic.Ypos;

		/*char str[20];
		sprintf(str, "%d", JoysticValueY);
		printf(str);
		printf("\n\n");
*/


		MCUFRIEND_kbv_print_tail(&Background[(320 * 40)], 0, 40, 320, 80);
		imagesoverlay(&BirdOne, &Background, actual_sprint_buffer2, 320, JoysticValueX, JoysticValueY,
				0, 0, 0, 0, 16, 16, 0Xffffff);
		MCUFRIEND_kbv_print_tail(&actual_sprint_buffer2, JoysticValueX, JoysticValueY, 16, 16);

	}

}


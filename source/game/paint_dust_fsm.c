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
 * 				This function allows to eliminate a pig or a block
 *				of the matrices of the game if it is necessary,
 *				then it paints a cloud of dust, in the coordinates
 *				given by the variables coorDustx and coorDusty.
 * --------------------------------------------------------------------------------------*/


#include "paint_dust_fsm.h"

uint8_t counter = 0;


bool paintDust(void) {

	/*---------------------------------------------------------------------------------------
	 *			Eliminate a pig, or a block of the matrices,
	 *			by putting a number that exceeds the limits
	 *			of the screen.
	 * --------------------------------------------------------------------------------------*/

	if (killPig) {
		matrix_pigs[PigToKill][0] = 500;
		matrix_pigs[PigToKill][1] = 500;
		killPig=false;
		paint_blocks();
	}
	if (destroyBlock) {
		matrix_blocks[BlockToDestroy][0] = 500;
		matrix_blocks[BlockToDestroy][1] = 500;
		destroyBlock=false;
		paint_blocks();
	}


	/*---------------------------------------------------------------------------------------
	*			Animates the cloud of dust, with 4 different images,
	*			and ends by painting the original background.
	* --------------------------------------------------------------------------------------*/

	switch ((counter / TimeDust)) {
	case 0:

		imagesoverlay((unsigned short *) DustOne, (unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, coorDustx,
				coorDusty, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coorDustx, coorDusty, 16,
				16);
		break;

	case 1:

		imagesoverlay((unsigned short *) DustTwo, (unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, coorDustx,
				coorDusty, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coorDustx, coorDusty, 16,
				16);
		break;

	case 2:

		imagesoverlay((unsigned short *) DustThree,
				(unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, coorDustx,
				coorDusty, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coorDustx, coorDusty, 16,
				16);
		break;

	case 3:

		imagesoverlay((unsigned short *) DustFour,
				(unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, coorDustx,
				coorDusty, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coorDustx, coorDusty, 16,
				16);
		break;

	case 4:
		imagesoverlay((unsigned short *) white, (unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, coorDustx,
				coorDusty, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coorDustx, coorDusty, 16,
				16);
		break;

	default:
		counter = 0;
		return true;
	}

	counter++;
	return false;
}

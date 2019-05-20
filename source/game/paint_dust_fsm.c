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

uint8_t tile_counter = 0;


bool paint_dust(void) {

	/*---------------------------------------------------------------------------------------
	 *			Eliminate a pig, or a block of the matrices,
	 *			by putting a number that exceeds the limits
	 *			of the screen.
	 * --------------------------------------------------------------------------------------*/

	if (kill_pig) {
		matrix_pigs[pig_to_kill][0] = 500;
		matrix_pigs[pig_to_kill][1] = 500;
		kill_pig=false;
		paint_blocks();
	}
	if (destroy_block) {
		matrix_blocks[block_to_destroy][0] = 500;
		matrix_blocks[block_to_destroy][1] = 500;
		destroy_block=false;



	}


	/*---------------------------------------------------------------------------------------
	*			Animates the cloud of dust, with 4 different images,
	*			and ends by painting the original background.
	* --------------------------------------------------------------------------------------*/

	switch ((tile_counter / DUST_DURATION)) {
	case 0:

		imagesoverlay((unsigned short *) DustOne,Background,
				(unsigned short *) actual_sprint_buffer, 320, coor_dusty_x,
				coor_dusty_y, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coor_dusty_x, coor_dusty_y, 16,
				16);
		break;

	case 1:

		imagesoverlay((unsigned short *) DustTwo, Background,
				(unsigned short *) actual_sprint_buffer, 320, coor_dusty_x,
				coor_dusty_y, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coor_dusty_x, coor_dusty_y, 16,
				16);
		break;

	case 2:

		imagesoverlay((unsigned short *) DustThree,
				Background,
				(unsigned short *) actual_sprint_buffer, 320, coor_dusty_x,
				coor_dusty_y, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coor_dusty_x, coor_dusty_y, 16,
				16);
		break;

	case 3:

		imagesoverlay((unsigned short *) DustFour,
				Background,
				(unsigned short *) actual_sprint_buffer, 320, coor_dusty_x,
				coor_dusty_y, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coor_dusty_x, coor_dusty_y, 16,
				16);
		break;

	case 4:
		imagesoverlay((unsigned short *) white,Background,
				(unsigned short *) actual_sprint_buffer, 320, coor_dusty_x,
				coor_dusty_y, 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, coor_dusty_x, coor_dusty_y, 16,
				16);
		break;

	default:
		tile_counter = 0;
		return true;
	}

	tile_counter++;
	return false;
}

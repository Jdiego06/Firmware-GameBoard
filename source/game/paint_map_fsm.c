#include "paint_map_fsm.h"

int matrix_pigs[3][2] = { { 100, 80 }, { 150, 100 }, { 200, 150 } };
int matrix_blocks[3][2] = { { 100, 96 }, { 150, 116 }, { 200, 166 } };

void paintBackground(void) {
	//paint Background
	MCUFRIEND_kbv_fillBMP(Background);

}

void paint_lifes(void) {

	MCUFRIEND_kbv_print_tail((const unsigned short *) Background, 0, 0, 320,
			20);

//Paint Birds of lifes
	for (int i = 0; i < remaining_shots; ++i) {

		imagesoverlay((unsigned short *) Bird, (unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, 16 * i + 3 * i, 4,
				0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, 16 * i + 3 * i, 4, 16,
				16);
	}
	LastX = 35;
	LastY = 75;

	// DELETE DOWN BAND
	//MCUFRIEND_kbv_print_tail(&Background[(320 * 188)], 0, 188, 320, 30);

}

void paint_pigs(void) {

	for (int i = 0; i < 3; i++) {
		imagesoverlay((unsigned short *) PigThree,
				(unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, matrix_pigs[i][0],
				matrix_pigs[i][1], 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, matrix_pigs[i][0],
				matrix_pigs[i][1], 16, 16);

		imagesoverlay((unsigned short *) BlockTwo,
				(unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320,
				matrix_blocks[i][0], matrix_blocks[i][1], 0, 0, 0, 0, 16, 16,
				0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, matrix_blocks[i][0],
				matrix_blocks[i][1], 16, 16);
	}

}

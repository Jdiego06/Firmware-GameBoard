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
 * 				This code implements several functions that are responsible
 * 				for painting the various elements of the game, such as blocks
 * 				and pigs, as well as the initial cover, and the background.
 * --------------------------------------------------------------------------------------*/

#include "paint_map_fsm.h"

/*---------------------------------------------------------------------------------------
 *						Arrays of pointers to tiles and object matrices
 * --------------------------------------------------------------------------------------*/

const unsigned short* piggs[3] = { PigOne, PigTwo, PigThree };
const unsigned short* birds[3] = { BirdOne, BirdTwo, BirdThree };

//const unsigned short* Backrounds[1] = { Background_1}; //, Background_2 };
//const unsigned short Background[76800] = { };

int matrix_pigs[3][2] = { };
int matrix_blocks[3][2] = { };

/*---------------------------------------------------------------------------------------
 *			Matrices of elements: The coordinates (x , y) of the pigs and
 *			blocks are defined, which will be drawn in the game.
 * --------------------------------------------------------------------------------------*/

int matrix_pigs0[3][2] = { { 100, 80 }, { 180, 40 }, { 220, 135 } };
int matrix_blocks0[3][2] = { { 100, 96 }, { 180, 56 }, { 220, 151 } };

int matrix_pigs1[3][2] = { { 90, 120 }, { 160, 60 }, { 200, 200 } };
int matrix_blocks1[3][2] = { { 90, 136 }, { 160, 76 }, { 200, 216 } };

int matrix_pigs2[3][2] = { { 120, 100 }, { 180, 40 }, { 280, 100 } };
int matrix_blocks2[3][2] = { { 120, 116 }, { 180, 56 }, { 280, 116 } };

/*---------------------------------------------------------------------------------------
 *				this function selects one of the worlds defined above
 * --------------------------------------------------------------------------------------*/

void SelectWorld(int world) {

	//int map=pseudoRandom(2);

	switch (world) {
	case 0:
		matriscopy(matrix_pigs, matrix_pigs0, 6);
		matriscopy(matrix_blocks, matrix_blocks0, 6);
		break;
	case 1:
		matriscopy(matrix_pigs, matrix_pigs1, 6);
		matriscopy(matrix_blocks, matrix_blocks1, 6);
		break;
	case 2:
		matriscopy(matrix_pigs, matrix_pigs2, 6);
		matriscopy(matrix_blocks, matrix_blocks2, 6);
		break;
	default:
		break;
	}
}

/*---------------------------------------------------------------------------------------
 *			           Paints the game's cover in a "random" way.
 * --------------------------------------------------------------------------------------*/

void paintCaratule(void) {
	int numero;
	numero = ((joystick.Xpos + joystick.Ypos) % 2);

	switch (numero) {
	case 0:
		MCUFRIEND_kbv_fillBMP(Caratula_1);
		break;
	case 1:
		MCUFRIEND_kbv_fillBMP(Caratula_1);
		break;
	}
}

/*---------------------------------------------------------------------------------------
 *			                   Paint the game background.
 * --------------------------------------------------------------------------------------*/

void paintBackground(int world) {

	/*switch (world) {
	case 0:
		matriscopy(Background, Backrounds[0], 76800);
		break;
	case 1:
		matriscopy(Background, Backrounds[0], 76800);
		break;
	default:
		break;
	}*/

	MCUFRIEND_kbv_fillBMP(Background);
}

/*---------------------------------------------------------------------------------------
 *			  Paint in the upper left corner of the screen, a number
 *			  of birds corresponding to the number of lives remaining
 *			  of the player minus one.
 * --------------------------------------------------------------------------------------*/

void paint_lifes(void) {

	MCUFRIEND_kbv_print_tail((const unsigned short *) Background, 0, 0, 320,
			20);

	for (int i = 0; i < remaining_shots - 1; ++i) {

		imagesoverlay((unsigned short *) Bird, (unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, 16 * i + 3 * i, 4,
				0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, 16 * i + 3 * i, 4, 16,
				16);
	}
	LastX = 35;
	LastY = 75;
}

/*---------------------------------------------------------------------------------------
 *			  Paint the pigs on the screen, according to the coordinates
 *			  given by matrix_pigs.
 * --------------------------------------------------------------------------------------*/

void paint_pigs(void) {

	for (int i = 0; i < 3; i++) {
		uint8_t PigNumber = pseudoRandom(2);
		imagesoverlay((unsigned short *) piggs[PigNumber],
				(unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320, matrix_pigs[i][0],
				matrix_pigs[i][1], 0, 0, 0, 0, 16, 16, 0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, matrix_pigs[i][0],
				matrix_pigs[i][1], 16, 16);
	}

}

/*---------------------------------------------------------------------------------------
 *			  Paint the blocks  on the screen, according to the coordinates
 *			  given by matrix_blocks.
 * --------------------------------------------------------------------------------------*/

void paint_blocks(void) {
	for (int i = 0; i < 3; i++) {
		imagesoverlay((unsigned short *) BlockTwo,
				(unsigned short *) Background,
				(unsigned short *) actual_sprint_buffer, 320,
				matrix_blocks[i][0], matrix_blocks[i][1], 0, 0, 0, 0, 16, 16,
				0Xffff);

		MCUFRIEND_kbv_print_tail(actual_sprint_buffer, matrix_blocks[i][0],
				matrix_blocks[i][1], 16, 16);
	}
}



/*---------------------------------------------------------------------------------------
 *			 Generates a number between 0 and 'range' according to the
 *			 current value of the pit
 * --------------------------------------------------------------------------------------*/

int pseudoRandom(uint8_t range) {
	int a = (int) PIT_GetCurrentTimerCount(PIT, kPIT_Chnl_0);
	return (int) (a % (range + 1));
}

/*---------------------------------------------------------------------------------------
 *                        			Copy matrix
 * --------------------------------------------------------------------------------------*/
void matriscopy(void * destmat, void * srcmat, int size) {
	memcpy(destmat, srcmat, size * sizeof(int));
}

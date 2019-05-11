/*----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <lecheverri@uco.edu.co> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 * Ing: Luis Felipe Echeverri
 * Company: UCO
 * Date: 27-04-2019
 * Project: Bomber Man
 * Description: this code implements the finite state machine frome play game,
 * 				the MCU begin at init state in this, the MCU print the wellcome
 * 				image in TFT, and pass to other state calling waitingforstart,
 * 				in this the MCU is waiting while the player press to BTNA button,
 * 				when this take place, the FSM jump to another state caller
 * 				painting_map when select a random map and paint it in the TFT,
 * 				after it the MCU jump to state gaming where the microcontroller
 * 				check the button BTNA for pause the game and call other two FSM
 * 				bomberman_fsm() & bomb_fsm() who manager the move of bomberman and
 * 				bomb manager.
 * ----------------------------------------------------------------------------*/

#include "game_fsm.h"
#include "utilities.h"
#include "Adafruit_GFX.h"
#include "fix_shot_fsm.h"

#include "../../drivers/custom/TFT/Fonts/AbRegular.h"
#include "../../drivers/custom/TFT/Fonts/angrybirds_regular12pt7b.h"

//#include "bomberman_fsm.h"
//#include "bomb_fsm.h"

#define TILE_W 16
#define TILE_H 16
#define SPANX 32
#define SPANY 32

uint16_t actual_sprint_buffer[(TILE_W + (2 * SPANX))
		* ((2 * SPANY) + (2 * TILE_H))]; //define size according to maximum convert image

game_states game_state = init;

//---------------------- Subroutines -----------------

void paintMap(void) {
	//paint Background
	MCUFRIEND_kbv_fillBMP(Background);
	//paint Bird
	imagesoverlay(BirdOne, Background, actual_sprint_buffer, 320, 35, 75, 0, 0,
			0, 0, 16, 16, 0Xffffff);
	MCUFRIEND_kbv_print_tail(actual_sprint_buffer, 35, 75, 16, 16);
}
/*
void paintCaratule(void) {
	int numero = 1;

	switch (numero) {
	case 0:
		MCUFRIEND_kbv_fillBMP(Caratula1);
		break;
	case 1:
		MCUFRIEND_kbv_fillBMP(Caratula2);
		break;
	case 2:
		MCUFRIEND_kbv_fillBMP(Caratula3);
		break;
	default:
		break;
	}
}*/

void game_fsm(void) {

	switch (game_state) {
	case init:
		MCUFRIEND_kbv_setRotation(1);
		Adafruit_GFX_setRotation(3);
		//paintCaratule();
		MCUFRIEND_kbv_fillBMP(Caratula1);
		Adafruit_GFX_setTextColorB(0xFFFF, 0x0000);
		Adafruit_GFX_setFont(&angrybirds_regular20pt7b);
		Adafruit_GFX_setCursor(0, 35);
		Adafruit_GFX_write_String((uint8_t *) "  Press Any Button");
		Adafruit_GFX_setCursor(5, 238);
		Adafruit_GFX_setFont(&angrybirds_regular12pt7b);
		Adafruit_GFX_write_String((uint8_t *) "ANGRY BIRDS");
		game_state = waitingforstart;
		break;

	case waitingforstart:
		if (BTNA_FLAG == 1 || BTNB_FLAG == 1) {
			BTNA_FLAG = 0;
			BTNB_FLAG = 0;
			game_state = painting_map;
		}

		break;

	case painting_map:
		paintMap();
		game_state = gaming;
		break;

	case gaming:

		if (BTNA_FLAG == 1) {
			BTNA_FLAG = 0;
			//PAINT GAME PAUSED MESSAGE
			Adafruit_GFX_setCursor(85, 120);
			Adafruit_GFX_write_String((uint8_t *) "Game Paused");
			game_state = pause;
		}

		fix_shot_fsm();
		//bomb_fsm();

		break;

	case pause:
		if (BTNA_FLAG == 1) {
			BTNA_FLAG = 0;
			//Clear announcement
			// Select background in position 320 in x, 240 in y, paint 30 px in y
			MCUFRIEND_kbv_print_tail(&Background[(320 * 100)], 0, 100, 320, 30);
			game_state = gaming;
		}
		break;

	case gameover:
		if (BTNA_FLAG == 1) {
			BTNA_FLAG = 0;
			game_state = painting_map;
		}
		break;
	}

}


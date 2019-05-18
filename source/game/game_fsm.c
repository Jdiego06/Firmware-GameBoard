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
#include "TFT/Fonts/AbRegular.h"
#include "TFT/Fonts/angrybirds_regular12pt7b.h"

//define size according to maximum convert image
uint16_t actual_sprint_buffer[(TILE_W + (2 * SPANX))
		* ((2 * SPANY) + (2 * TILE_H))];

//Initial Game State
game_states game_state = init;

//uint16_t *Bird = (uint16_t *) BirdOne;

//remaining_shots
int remaining_shots;
int coorDustx;
int coorDusty;
int PigToKill;
int BlockToDestroy;

bool killPig;
bool destroyBlock;

//---------------------- Subroutines -----------------

void paintCaratule(void) {
	int numero;
	numero = ((joystick.Xpos + joystick.Ypos) % 2);

	switch (numero) {
	case 0:
		MCUFRIEND_kbv_fillBMP(Caratula1);
		break;
	case 1:
		MCUFRIEND_kbv_fillBMP(Caratula2);
		break;
	}
}

bool ChekWin() {

	for (int i = 0; i < sizeof(matrix_pigs) / sizeof(matrix_pigs[0]); i++) {
		if (matrix_pigs[i][0] != 500) {
			return false;
		}
	}
	return true;
}

void game_fsm(void) {

	switch (game_state) {
	case init:
		MCUFRIEND_kbv_setRotation(1);
		Adafruit_GFX_setRotation(3);
		paintCaratule();
		//MCUFRIEND_kbv_fillBMP(Caratula1);
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
		//BTNA_FLAG = 0;
		//BTNB_FLAG = 0;
		remaining_shots = (INIT_SHOTS);
		paintBackground();
		paint_lifes();
		paint_pigs();
		paint_blocks();
		game_state = gaming;
		break;

	case gaming:

		if (BTNB_FLAG == 1) {
			BTNB_FLAG = 0;
			game_state = shot_bird;
		} else {
			fix_shot_fsm();
		}

		break;
	case shot_bird:
		shot_bird_fsm();
		remaining_shots--;
		game_state = draw_dust;
		break;

	case draw_dust:
		if (paintDust()) {
			if (ChekWin() || (remaining_shots == 0)) {
				game_state = gameover;
			} else {
				paint_lifes();
				game_state = gaming;
			}
		}
		break;

	case gameover:

		if (ChekWin()) {
			Adafruit_GFX_setCursor(100, 120);
			Adafruit_GFX_write_String((uint8_t *) "You Win");
		} else {
			Adafruit_GFX_setCursor(100, 120);
			Adafruit_GFX_write_String((uint8_t *) "You Loose");
		}
		Adafruit_GFX_setCursor(70, 150);
		Adafruit_GFX_write_String((uint8_t *) "Press Any Button");

		if (BTNA_FLAG == 1 || BTNB_FLAG == 1) {
			BTNA_FLAG = 0;
			BTNB_FLAG = 0;
			//MCUFRIEND_kbv_print_tail(&Background[(320 * 100)], 0, 100, 320, 30);
			game_state = init;
		}
		break;
	default:
		game_state = painting_map;
	}

}


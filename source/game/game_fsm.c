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
 * 				This code implements the finite state machine from play game,
 * 				the MCU begin at init state in this, the MCU print the welcome
 * 				image in TFT, and pass to other state calling waitingforstart,
 * 				in this the MCU is waiting while the player press to BTNA or BTNB
 * 				button, when this take place, the FSM jump to another state caller
 * 				painting_map when select a background, positions of blocks, and pigs
 * 				after it the MCU jump to state gaming where the player can fix the
 * 				shot, then the fsm check the button BTNB, and if this is pressed shot
 * 				the bird. After fms go to the paindust state where draw a dust cloud
 * 				in the last bird position , and finally the fsm check game over and
 * 				print: "You win" or "You lose" in TFT.
 * --------------------------------------------------------------------------------------*/

#include "game_fsm.h"
#include "TFT/Fonts/AbRegular.h"
#include "TFT/Fonts/angrybirds_regular12pt7b.h"

/*    Variables, used for by other fsm(s)    */
uint16_t coor_dusty_x;
uint16_t coor_dusty_y;
uint8_t remaining_shots;

uint8_t pig_to_kill;
uint8_t block_to_destroy;
bool kill_pig;
bool destroy_block;

uint16_t actual_sprint_buffer[(TILE_WIDHT + (2 * SPANX))
		* ((2 * SPANY) + (2 * TILE_HEIGHT))];

/*    State initial if the game (after reset)    */
game_states game_state = init;

/*    Initial world (after reset)    */
uint8_t world = 0;

/*    Initial shots (after reset)    */
uint8_t remaining_shots = LEVEL_SHOTS;

/*---------------------------------------------------------------------------------------
 * 			This function verifies if all the pigs have been destroyed.
 * --------------------------------------------------------------------------------------*/

bool check_win() {
	for (int i = 0; i < sizeof(matrix_pigs) / sizeof(matrix_pigs[0]); i++) {
		if (matrix_pigs[i][0] != 500) {
			return false;
		}
	}
	return true;
}

/*---------------------------------------------------------------------------------------
 * 			This is the main machine of the game, it controls the flow of the program,
 * 			and the current state in which the game is located
 *--------------------------------------------------------------------------------------*/

void game_fsm(void) {
	switch (game_state) {

	case init:
		MCUFRIEND_kbv_setRotation(1);
		Adafruit_GFX_setRotation(3);
		paint_caratule();
		Adafruit_GFX_setTextColorB(0xFFFF, 0x0000);
		Adafruit_GFX_setFont(&angrybirds_regular20pt7b);
		Adafruit_GFX_setCursor(0, 35);
		Adafruit_GFX_write_String((uint8_t *) "  Press Any Button");
		Adafruit_GFX_setCursor(5, 238);
		Adafruit_GFX_setFont(&angrybirds_regular12pt7b);
		Adafruit_GFX_write_String((uint8_t *) "ANGRY BIRDS");
		game_state = waiting_for_start;
		break;

	case waiting_for_start:
		if (BTNA_FLAG == 1 || BTNB_FLAG == 1) {
			BTNA_FLAG = 0;
			BTNB_FLAG = 0;
			game_state = painting_map;
		}
		break;

	case painting_map:
		select_background(world);
		select_world(world);
		select_bird(world);
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
		if (paint_dust()) {
			if (check_win() || (remaining_shots == 0)) {
				game_state = game_over;
			} else {
				paint_lifes();
				game_state = gaming;
			}
		}
		break;

	case game_over:
		BTNA_FLAG = 0;
		BTNB_FLAG = 0;
		if (check_win()) {
			Adafruit_GFX_setCursor(120, 120);
			Adafruit_GFX_write_String((uint8_t *) "You Win");
			remaining_shots += LEVEL_SHOTS;
			world++;
		} else {
			Adafruit_GFX_setCursor(100, 120);
			Adafruit_GFX_write_String((uint8_t *) "You Lose");
			remaining_shots = LEVEL_SHOTS;
			world = 0;
		}
		Adafruit_GFX_setCursor(70, 150);
		Adafruit_GFX_write_String((uint8_t *) "Press Any Button");

		if (world == WORLDS_NUMBER) {
			game_state = game_complete;
		} else {
			game_state = waiting_for_start;
		}

		break;

	case game_complete:
		if (BTNA_FLAG == 1 || BTNB_FLAG == 1) {
			BTNA_FLAG = 0;
			BTNB_FLAG = 0;
			game_state = init;
		}
		break;

	default:
		game_state = painting_map;
	}

}


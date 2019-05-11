
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
 * Description: This code implements detection of BTNA and BTNB of game board
 * 				Additionally, this driver enable the haptic feedback during
 * 				HAPTIC_TICKS time defined in the BUTTON.h file
 * ----------------------------------------------------------------------------*/

#ifndef _BOARD_H_
#define _BOARD_H_

/* * ----------------------------------------------------------------------------
 * @brief:	The following configuration is for the game board version 2019
 * 			of embedded system course
 * ----------------------------------------------------------------------------*/

#define BOARD_NAME "GAMEBOARD-2019"
#define BOARD_BTNA_GPIO GPIOB
#define BOARD_BTNA_PORT PORTB
#define BOARD_BTNA_PIN 3u
#define BOARD_BTNA_PRESSED 1u
#define BOARD_BTNA_IRQn PORTB_IRQn
#define BOARD_BTNA_IRQHandler PORTB_IRQHandler

#define BOARD_BTNB_GPIO GPIOB
#define BOARD_BTNB_PORT PORTB
#define BOARD_BTNB_PIN 2u
#define BOARD_BTNB_PRESSED 1u
#define BOARD_BTNB_IRQn PORTB_IRQn
#define BOARD_BTNB_IRQHandler PORTB_IRQHandler


#define BOARD_HAPTIC_GPIO GPIOA
#define BOARD_HAPTIC_PORT PORTA
#define BOARD_HAPTIC_PIN 15u

#endif /* _BOARD_H_ */



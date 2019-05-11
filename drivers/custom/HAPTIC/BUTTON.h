
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
 * ----------------------------------------------------------------------------*/

#ifndef CUSTOM_BUTTON_H_
#define CUSTOM_BUTTON_H_

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_lptmr.h"
#include "HAPTIC_PIN.h"
#include "../GLOBAL.h"

#define HAPTIC_TICKS 100
#define DEBOUNCE_TICKS 20

void BUTTON_Init(void);

#endif /* CUSTOM_BUTTON_H_ */

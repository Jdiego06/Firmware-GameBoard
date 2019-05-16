#include "paint_dust_fsm.h"

int counter = 0;
bool paintDust(void) {

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
		if (killPig) {
			matrix_pigs[PigToKill][0] = 500;
			matrix_pigs[PigToKill][1] = 500;
		}
		return true;
	}

	counter++;
	return false;
}

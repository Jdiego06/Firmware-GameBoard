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

#ifndef GAME_UTILITIES_H_
#define GAME_UTILITIES_H_
#include <stdint.h>

void imagesoverlay( unsigned short *image1, 		//image that will be in front
					unsigned short *background, 	//image that will behind
					unsigned short *image_result, 	//image that will behind
					int16_t w_background, 			//width of original background image
					int16_t x_background, 			//horizontal pixel of background will be put image1
					int16_t y_background, 			//vertical pixel of background will be put image1
					int16_t left_w_span, 			//width span to left
					int16_t rigth_w_span, 			//width span to right
					int16_t up_h_span,				//height span to up
					int16_t down_h_span,			//height span to down
					int16_t w, 						//width of the  image1
					int16_t h,						//height of the  image1
					uint16_t color);				//define the transparent color for image1

#endif /* GAME_UTILITIES_H_ */

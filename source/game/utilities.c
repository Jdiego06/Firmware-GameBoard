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
 * Description: this code implements a overlap of two images an store the result
 * 				in other the parameter is specified in function header,
 * 				keep in mind that the w_background is the complete size of
 * 				vector image that contain the background image
 * ----------------------------------------------------------------------------*/
#include "utilities.h"

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
					uint16_t color)					//define the transparent color for image1
					{

	uint16_t i=0,j=0,actual_row_pos_base=0,actual_pixel_pos, actual_row_background;
    uint16_t limity=(h+(down_h_span+up_h_span));
    uint16_t limitx=(w+(rigth_w_span+left_w_span));

	for(i=0;i<limity;i++){
		actual_row_pos_base=i*limitx;
		actual_row_background=(y_background-up_h_span+i)*w_background;
		for(j=0;j<limitx;j++){
			actual_pixel_pos=actual_row_pos_base+j;
			if( j>=left_w_span && j<w+left_w_span && i>=up_h_span && i<h+up_h_span ){
				if(*image1!=color){
					image_result[actual_pixel_pos]=*image1;
				}else{
					image_result[actual_pixel_pos]=background[((actual_row_background)+(x_background-left_w_span)+j)];
				}
				image1++;
			}else{
				image_result[actual_pixel_pos]=background[((actual_row_background)+(x_background-left_w_span)+j)];
			}
			//DEBUG:uncomment for show result in TFT first pixels block
			//Adafruit_GFX_writePixel(j, i, image_result[actual_pixel_pos]);

		}
	}
}

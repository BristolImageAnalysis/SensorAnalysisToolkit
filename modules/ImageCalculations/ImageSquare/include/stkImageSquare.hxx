/*
 * stkImageSquare.hxx
 *
 *  Created on: 14 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageSquare_hxx
#define __stkImageSquare_hxx

#include "stkImageSquare.h"
#include <algorithm>
#include <functional>



namespace stk{



template <typename T_Pixeldata> ImageSquare<T_Pixeldata>::ImageSquare(){}
template <typename T_Pixeldata> ImageSquare<T_Pixeldata>::~ImageSquare(){}



template <typename T_Pixeldata>

void ImageSquare<T_Pixeldata>::SquareImage( std::shared_ptr< stk::Image<T_Pixeldata> > SquareingImage){

		typename std::vector<T_Pixeldata>::iterator itFirstPixel =  SquareingImage->StartImage(); //set to start of the image
		typename std::vector<T_Pixeldata>::iterator itLastPixel =  SquareingImage->EndImage(); //set to end of image




		std::transform(itFirstPixel, itLastPixel, itFirstPixel, itFirstPixel, std::multiplies<T_Pixeldata>());//Multiplies each pixel by itself using the transform method.

}
}


#endif /* __stkImageSquare_hxx */

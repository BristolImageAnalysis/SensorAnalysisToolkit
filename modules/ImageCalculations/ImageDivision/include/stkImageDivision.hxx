/*
 * stkImageDivision.hxx
 *
 *  Created on: 9 Jun 2015
 *      Author: phrfp
 */

#ifndef __stkImageDivision_hxx
#define __stkImageDivision_hxx

#include "stkImageDivision.h"
#include <algorithm>
#include <functional>

namespace stk{

ImageDivision::ImageDivision(){}

 ImageDivision::~ImageDivision(){}

 template<typename T_PixelOutputType>
void ImageDivision::DivideImage( std::shared_ptr< stk::Image<T_PixelOutputType> > dividendImage, const T_PixelOutputType &divisor ){

	typename std::vector<T_PixelOutputType>::iterator itFirstPixel =  dividendImage->StartImage(); //set to start of the image
	typename std::vector<T_PixelOutputType>::iterator itLastPixel =  dividendImage->EndImage(); //set to end of image

			std::transform( itFirstPixel, itLastPixel, itFirstPixel,
			std::bind2nd(std::divides<T_PixelOutputType>(), divisor)  );//use the transform method to calculate the result of the division

}

}

#endif /* __stkImageDivision_hxx */

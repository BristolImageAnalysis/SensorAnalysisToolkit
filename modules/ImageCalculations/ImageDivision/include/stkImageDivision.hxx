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

template <typename T_Pixeltype> ImageDivision<T_Pixeltype>::ImageDivision(){}

template <typename T_Pixeltype> ImageDivision<T_Pixeltype>::~ImageDivision(){}

template <typename T_Pixeltype>
void ImageDivision<T_Pixeltype>::DivideImage( std::shared_ptr< stk::Image<T_Pixeltype> > dividendImage, const T_Pixeltype &divisor ){

	typename std::vector<T_Pixeltype>::iterator itFirstPixel =  dividendImage->StartImage(); //set to start of the image
	typename std::vector<T_Pixeltype>::iterator itLastPixel =  dividendImage->EndImage(); //set to end of image

	std::transform( itFirstPixel, itLastPixel, itFirstPixel,
			std::bind2nd(std::divides<T_Pixeltype>(), divisor)  );//use the transform method to calculate the result of the division

}

}

#endif /* __stkImageDivision_hxx */

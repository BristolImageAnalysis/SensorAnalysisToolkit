/*
 * stkImageSubract.hxx
 *
 *  Created on: 14 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageSubtract_hxx
#define __stkImageSubtract_hxx

#include <algorithm>
#include <functional>
#include "stkImageSubtract.h"

namespace stk{


ImageSubtract::ImageSubtract(){}
ImageSubtract::~ImageSubtract(){}

template< typename T_PixelInputType, typename T_PixelOutputType>
void ImageSubtract::SubtractImageStack( const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack, std::shared_ptr < stk::Image<T_PixelOutputType> > result ){

	typename std::vector<T_PixelInputType>::iterator itFrameStart;
	typename std::vector<T_PixelInputType>::iterator itFrameEnd;
	typename std::vector<T_PixelOutputType>::iterator itResult;

	for(int iFrames=0; iFrames < imageStack->NumberOfImageInStack(); iFrames++){

		itFrameStart = imageStack->StartOfFrame(iFrames);
		itFrameEnd = imageStack->EndOfFrame(iFrames);
		itResult = result->StartImage();
		std::transform( itFrameStart, itFrameEnd, itResult, itResult, std::minus<T_PixelOutputType>() );

	}
}




}


#endif /* __stkImageSubtract_hxx */

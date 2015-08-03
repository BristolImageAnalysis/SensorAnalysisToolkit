/*============================
 * stkImageSum.hxx
 *
 *  Created on: 8 Jun 2015
 *      Author: phrfp
 *=============================*/

#ifndef __stkImageSum_hxx
#define __stkImageSum_hxx

#include <algorithm>
#include <functional>
#include "stkImageSum.h"

namespace stk{


ImageSum::ImageSum(){}


ImageSum::~ImageSum(){}

//template <typename T_Pixeldata>
//void ImageSum<T_Pixeldata>::SumImageStack( const std::shared_ptr< stk::ImageStack<T_Pixeldata> > imageStack, std::shared_ptr < stk::Image<T_Pixeldata> > result ){
//
//	for(int iFrames=0; iFrames < imageStack->NumberOfImageInStack(); iFrames++ ){//loop over all the frames in the stack
//		for( int iElements=0; iElements < result->NumberOfPixels(); iElements++ ){//loop over all the pixels in the result
//			T_Pixeldata tempPixel = imageStack->GetPixelAt( ((iFrames*result->NumberOfPixels()) + iElements) ); //get stack value
//			tempPixel += result->GetPixelAt( iElements ); //Add to this the element of the element
//			result->SetPixelAt( iElements, tempPixel );//update the image value
//
//		}
//	}
//}

template< typename T_PixelInputType, typename T_PixelOutputType>
void ImageSum::SumImageStack( const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack, std::shared_ptr < stk::Image<T_PixelOutputType> > result ){

	typename std::vector<T_PixelInputType>::iterator itFrameStart;
	typename std::vector<T_PixelInputType>::iterator itFrameEnd;
	typename std::vector<T_PixelOutputType>::iterator itResult;

	for(int iFrames=0; iFrames < imageStack->NumberOfImageInStack(); iFrames++)

	{
		itFrameStart = imageStack->StartOfFrame(iFrames);
		itFrameEnd = imageStack->EndOfFrame(iFrames);
		itResult = result->StartImage();
		std::transform( itFrameStart, itFrameEnd, itResult, itResult, std::plus<T_PixelOutputType>() );
		//std::cout<<iFrames<<std::endl;
	}
}

}
#endif /* __stkImageSum_hxx */

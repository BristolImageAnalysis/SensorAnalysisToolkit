/*
 * stkImageMinus.hxx
 *
 *  Created on: 17 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageMinus_hxx
#define __stkImageMinus_hxx

#include <algorithm>
#include <functional>
#include "stkImageMinus.h"




namespace stk{

ImageMinus::ImageMinus(){}
ImageMinus::~ImageMinus(){}

template< typename T_PixelInputType, typename T_PixelOutputType>
void ImageMinus::MinusImage(const std::shared_ptr <stk::ImageStack<T_PixelInputType> > imageStack, const std::shared_ptr <stk::Image<T_PixelOutputType> > myImage){


		typename std::vector<T_PixelInputType>::iterator itFrameStart;
		typename std::vector<T_PixelInputType>::iterator itFrameEnd;
		typename std::vector<T_PixelOutputType>::iterator itPedStart;

		for(int iFrames=0; iFrames < imageStack->NumberOfImageInStack(); iFrames++){

				itFrameStart = imageStack->StartOfFrame(iFrames);
				itFrameEnd = imageStack->EndOfFrame(iFrames);
				itPedStart = myImage->StartImage();
				std::transform( itFrameStart, itFrameEnd, itPedStart, itFrameStart, std::minus<T_PixelInputType>() );

			}
}


template<typename T_PixelOutputType>
void ImageMinus::MinusImage(const std::shared_ptr <stk::Image<T_PixelOutputType> > myImage, const std::shared_ptr <stk::Image<T_PixelOutputType> > subtractImage){


		typename std::vector<T_PixelOutputType>::iterator itFrameStart;
		typename std::vector<T_PixelOutputType>::iterator itFrameEnd;
		typename std::vector<T_PixelOutputType>::iterator itSubStart;



				itFrameStart = myImage->StartImage();
				itFrameEnd = myImage->EndImage();
				itSubStart = subtractImage->StartImage();
				std::transform( itFrameStart, itFrameEnd, itSubStart, itFrameStart, std::minus<T_PixelOutputType>() );


}


template<typename T_PixelInputType ,typename T_PixelOutputType>
	void ImageMinus::MinusImage(const std::shared_ptr <stk::ImageStack<T_PixelInputType> > imageStack, const std::shared_ptr< stk::Image<T_PixelOutputType> > subtractImage, const std::shared_ptr< stk::Image<T_PixelOutputType> > outputImage, int darkFrames, int darkFramesAfter){

	tbb::parallel_for(darkFrames, darkFramesAfter, [&](int iFrames)
			{

					for(int iElements=0; iElements<subtractImage->NumberOfPixels();iElements++){
							T_PixelOutputType temp = imageStack->GetPixelAt(iFrames*subtractImage->NumberOfPixels()+iElements)-subtractImage->GetPixelAt(iElements);
							T_PixelOutputType outTemp = outputImage->GetPixelAt(iElements);
							outTemp= outTemp+temp;
							outputImage->SetPixelAt(iElements,outTemp );
					}

				});

}
}




#endif /* __stkImageMinus_hxx */

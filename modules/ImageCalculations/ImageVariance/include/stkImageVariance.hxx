/*
 * stkImageVariance.hxx
 *
 *  Created on: 15 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageVariance_hxx
#define __stkImageVariance_hxx

#include <algorithm>
#include <functional>
#include "stkImageVariance.h"




namespace stk{


ImageVariance::ImageVariance(){}

ImageVariance::~ImageVariance(){}

template< typename T_PixelInputType, typename T_PixelOutputType>
void ImageVariance::VarianceImageStack(const std::shared_ptr<stk::ImageStack<T_PixelInputType> > imagestack, const std::shared_ptr<stk::Image<T_PixelOutputType> > pedestal, std::shared_ptr<stk::Image<T_PixelOutputType> > result ){



			tbb::parallel_for(0, imagestack->NumberOfImageInStack(), [&](int iFrames)
					{

								tbb::parallel_for(0, pedestal->NumberOfPixels(), [&](int iElements)

										{
										T_PixelOutputType temp = imagestack->GetPixelAt(iFrames*pedestal->NumberOfPixels()+iElements)-pedestal->GetPixelAt(iElements);
										T_PixelOutputType outTemp = result->GetPixelAt(iElements);
										outTemp= outTemp+(temp*temp);
										result->SetPixelAt(iElements,outTemp );
								} );

							} );



		stk::ImageDivision myDivider;
		myDivider.DivideImage(result, static_cast<T_PixelOutputType>(imagestack->NumberOfImageInStack()) );



}





}

#endif /* __stkImageVariance_hxx */

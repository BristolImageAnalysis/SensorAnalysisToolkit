/*
 * stkImageFlatFieldCorrection.hxx
 *
 *  Created on: 22 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageFlatFieldCorrection_hxx
#define __stkImageFlatFieldCorrection_hxx


#include "stkImageFlatFieldCorrection.h"
#include <algorithm>
#include <functional>
#include <vector>


namespace stk{

ImageFlatFieldCorrection::ImageFlatFieldCorrection(){}
ImageFlatFieldCorrection::~ImageFlatFieldCorrection(){}

template< typename T_PixelInputType, typename T_PixelOutputType>
void ImageFlatFieldCorrection::CorrectImage(std::shared_ptr<stk::ImageStack<T_PixelInputType> > lightStack, std::shared_ptr<stk::Image<T_PixelOutputType> > pedImage, std::shared_ptr<stk::Image<T_PixelOutputType> > rawImage, std::shared_ptr<stk::Image<T_PixelOutputType> > gainImage){



	/*
	 * Prepare the light image
	 */
	std::shared_ptr< stk::Image<float> > lightImage ( new stk::Image<float>(4096,4096) );

	stk::ImageSum summer;
	stk::ImageDivision divider;
	T_PixelOutputType num = lightStack->NumberOfImageInStack();
	summer.SumImageStack(lightStack, lightImage);

	divider.DivideImage(lightImage, static_cast<float>(lightStack->NumberOfImageInStack()) );

	/*s
	 * Calculating m
	 */

	stk::ImageMinus subtracter;


	subtracter.MinusImage(lightImage, pedImage);
	T_PixelOutputType tempPixel=0;

	for(int iElements=0; iElements<lightImage->NumberOfPixels(); iElements++)
	{
			tempPixel = tempPixel + lightImage->GetPixelAt(iElements);

	}


	T_PixelOutputType m = tempPixel/(lightImage->NumberOfPixels());

	/*
	 * Calculating Gain
	 *
	 */
	tbb::parallel_for(0, lightImage->NumberOfPixels(), [&](int iElements)
	{
		if(lightImage->GetPixelAt(iElements)==0){
			gainImage->SetPixelAt(iElements, 0);
		}
		else{
			T_PixelOutputType tempgain = (m/(lightImage->GetPixelAt(iElements)));

			if(tempgain>1.16||tempgain<0.88){
				gainImage->SetPixelAt(iElements, 0);
			}
			else{
				gainImage->SetPixelAt(iElements, tempgain);
			}



		}
	});



	/*
	 * Calculaete corrected Image
	 */

	//subtracter.MinusImage(rawImage, pedImage);
	typename std::vector<T_PixelOutputType>::iterator itFirstPixel =  rawImage->StartImage(); //set to start of the image
	typename std::vector<T_PixelOutputType>::iterator itLastPixel =  rawImage->EndImage(); //set to end of image
	typename std::vector<T_PixelOutputType>::iterator itPixel  = gainImage->StartImage();
	std::transform(itFirstPixel, itLastPixel, itPixel, itFirstPixel, std::multiplies<T_PixelOutputType>());//Multiplies each pixel by itself using the transform method.







}
}


#endif /* __stkImageFlatFieldCorrection_hxx */

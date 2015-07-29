/*
 * stkImageFlatFieldCorrection.h
 *
 *  Created on: 22 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageFlatFieldCorrection_h
#define __stkImageFlatFieldCorrection_h


#include "stkImage.h"
#include "stkImageStack.h"
#include "stkImageSum.h"
#include "stkImageDivision.h"
#include "stkImageMinus.h"
#include "tbb/tbb.h"

namespace stk{
/**
 * \class ImageFlatFieldCorrection
 * \brief ImageFlatFieldCorrection class uses light and dark image stacks to calculate the gain for each pixel. Input image is then corrected using these values.
 *
 * ImageFlatFieldCorrection class takes a light and dark image stack to find the average difference. The gain for each pixel calculated and the input image is corrected.
 */

class ImageFlatFieldCorrection{

public:
	/**
	 * Default constructor
	 */
	ImageFlatFieldCorrection();
	/**
	 * Destructor
	 */

	virtual ~ImageFlatFieldCorrection();

	/**
	 * Function to take a light image stack, a pedestal image and a raw image to output a gain map and flat field corrected image.
	 * @par[in] lightStack The input stack of light images.
	 * @par[in] pedImage The pedestal image.
	 * @par[in] rawImage The input image to be corrected.
	 * @par[in] gainImage Image containing gain values for each pixel.
	 */
	template< typename T_PixelInputType, typename T_PixelOutputType>
	void CorrectImage(std::shared_ptr<stk::ImageStack<T_PixelInputType> > lightStack, std::shared_ptr<stk::Image<T_PixelOutputType> > pedImage, std::shared_ptr<stk::Image<T_PixelOutputType> > rawImage, std::shared_ptr<stk::Image<T_PixelOutputType> > gainImage);
};


}


#include "stkImageFlatFieldCorrection.hxx"


#endif /* __stkImageFlatFieldCorrection_h */

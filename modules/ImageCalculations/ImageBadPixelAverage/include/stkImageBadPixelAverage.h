/*
 * stkImageBadPixelAverage.h
 *
 *  Created on: 17 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageBadPixelAverage_h
#define __stkImageBadPixelAverage_h

#include "stkImage.h"
#include "stkImageStack.h"


namespace stk{
/**
 * \class BadPixelAverage
 * \brief BadPixelAverage class takes the image input and a mask image to apply an average function to bad pixels.
 *
 * BadPixelAverage class uses a mask image to identify bad pixels. The pixels are then averaged using the eight nearest neighbors and is output back into the input image.
 *
 */



class ImageBadPixelAverage{

	/**
	* Default constructor
	*
	*/
public:
	ImageBadPixelAverage();

	/**
	* Destructor
	*
	*/
	virtual ~ImageBadPixelAverage();
	 /**
	     * Outputs the averaged pixels back into original image stack based on mask information.
	     * @par[in] imageStack The input image stack. Will become output file.
	     * @par[in] maskingImage Mask image file containing location of bad pixels.
	     */
	template< typename T_PixelInputType>
	void BadPixelAverage(const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack, std::shared_ptr< stk::Image<bool> > maskingImage);

	/**
		     * Outputs the averaged pixels back into original image based on mask information.
		     * @par[in] image The input image. Will become output file.
		     * @par[in] maskingImage Mask image file containing location of bad pixels.
		     */

	template<typename T_PixelOutputType>
	void BadPixelAverage(const std::shared_ptr< stk::Image<T_PixelOutputType> > imageInput, std::shared_ptr< stk::Image<bool> > maskingImage);


};

}

#include "stkImageBadPixelAverage.hxx"


#endif /* __stkImageBadPixelAverage_h */

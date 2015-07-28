/*
 * stkImageResize.h
 *
 *  Created on: 21 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageResize_h
#define __stkImageResize_h


#include "stkImage.h"
#include "tbb/tbb.h"
namespace stk{

/**
 * \class ImageResize
 * \brief ImageResize class that resizes input image to a quarter of its original size.
 *
 * ImageResize class takes input image and resizes it to a quarter of its original size by taking an average of a 4x4 area of pixels.
 */

class ImageResize{

public:
	/**
		 * Default constructor
		 *
		 */
	ImageResize();
	/**
		 * Destructor
		 *
		 */

	virtual ~ImageResize();
	/**
		 * Function to resize input image and output into new image.
		 * @par[in] resizeImage The input image.
		 * @par[in] resultImage The output resized image.
		 */
	template<typename T_PixelOutputType>
	void ResizeImage(std::shared_ptr< stk::Image<T_PixelOutputType> > resizeImage, std::shared_ptr< stk::Image<T_PixelOutputType> > resultImage);



};
}

#include "stkImageResize.hxx"


#endif /* __stkImageResize_h */

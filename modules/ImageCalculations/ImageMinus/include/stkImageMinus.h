/*
 * stkImageMinus.h
 *
 *  Created on: 17 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageMinus_h
#define __stkImageMinus_h

#include "stkImage.h"
#include "stkImageStack.h"



namespace stk{

/**
 * \class ImageMinus
 * \brief ImageMinus class that subtracts images from images, or images from image stacks.
 *
 * ImageMinus class takes image or image stacks and subtracts a given image. Can output to input image or a separate output image.
 */


class ImageMinus{

public:
	/**
	 * Default constructor
	 *
	 */
	ImageMinus();
	/**
	 * Destructor
	 */

	virtual ~ImageMinus();
	/**
	 * Function to remove input image from each frame of stack then return into the stack.
	 * @par[in] imageStack The input image stack
	 * @par[in] myImage The image to subtract from stack.
	 */
	template< typename T_PixelInputType, typename T_PixelOutputType>
	void MinusImage(const std::shared_ptr <stk::ImageStack<T_PixelInputType> > imageStack, const std::shared_ptr <stk::Image<T_PixelOutputType> > myImage);
	/**
		 * Function to remove subtract image from input image and return to input image.
		 * @par[in] myImage The input image.
		 * @par[in] subtractImage The image to subtract from input image.
		 */
	template<typename T_PixelOutputType>
	void MinusImage(const std::shared_ptr <stk::Image<T_PixelOutputType> > myImage, const std::shared_ptr< stk::Image<T_PixelOutputType> > subtractImage);
	/**
		 * Function to remove subtract image from input image and return to output image.
		 * @par[in] myImage The input image.
		 * @par[in] subtractImage The image to subtract from input image.
		 * @par[in] outputImage The output image.
		 */
	template<typename T_PixelInputType ,typename T_PixelOutputType>
	void MinusImage(const std::shared_ptr <stk::ImageStack<T_PixelInputType> > myImage, const std::shared_ptr< stk::Image<T_PixelOutputType> > subtractImage, const std::shared_ptr< stk::Image<T_PixelOutputType> > outputImage, int darkFrames, int darkFramesAfter);
};


}

#include "stkImageMinus.hxx"


#endif /* __stkImageMinus_h */

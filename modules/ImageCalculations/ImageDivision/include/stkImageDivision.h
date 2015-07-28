/*=============================
 * stkImageDivision.h
 *
 *  Created on: 9 Jun 2015
 *      Author: phrfp
 *=============================*/

#ifndef __stkImageDivision_h
#define __stkImageDivision_h

#include "stkImage.h"

namespace stk{

/**
 *\class ImageDivision
 *\brief Image division class allows images to be divided.
 *
 *Class to allow an image to be divided through.
 *
 */

//template <typename T_Pixeltype>
class ImageDivision{
public:
	/**
	 * Default constructor
	 */
	ImageDivision();
	/**
	 * Default destructor
	 */
	virtual ~ImageDivision();

	/**
	 * Function that divides all the pixels in an image by a constant.
	 * @par[in] dividendImage Image containing pixels that will be divided.
	 * @par[in] divisor Constant that each pixel will be divided by.
	 */
	template< typename T_PixelOutputType>
	void DivideImage( std::shared_ptr< stk::Image<T_PixelOutputType> > dividendImage, const T_PixelOutputType &divisor );

};

}

#include "stkImageDivision.hxx"

#endif /* __stkImageDivision_h */

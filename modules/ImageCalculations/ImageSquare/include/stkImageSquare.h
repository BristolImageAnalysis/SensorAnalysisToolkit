/*
 * stkImageSumOfSquares.h
 *
 *  Created on: 13 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageSquare_h
#define __stkImageSquare_h

#include "stkImage.h"
#include "stkImageStack.h"


namespace stk {

template <typename T_Pixeldata>
class ImageSquare{
public:
	/*Default constructor
	 *
	 *
	 */
	ImageSquare();
	/*Default destructor
	 *
	 *
	 */
	virtual ~ImageSquare();

	/*Function to square an image. [1 2] becomes [1 4]
	 *
	 *
	 *
	 */
	void SquareImage( std::shared_ptr< stk::Image<T_Pixeldata> > SquareingImage);

};
}

#include "stkImageSquare.hxx"

#endif /* __stkImageSquare_h */

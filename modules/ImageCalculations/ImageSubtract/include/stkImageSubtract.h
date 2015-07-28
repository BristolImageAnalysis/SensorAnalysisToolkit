/*
 * stkImageSubtract.h
 *
 *  Created on: 14 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageSubtract_h
#define __stkImageSubtract_h

#include "stkImage.h"
#include "stkImageStack.h"


namespace stk{


class ImageSubtract{

public:
	/*
	 *Default constructor
	 */
	ImageSubtract();
	/*
	 * Default destructor
	 */

	virtual ~ImageSubtract();

	/*
	 * Function to subtract.
	 */
	template< typename T_PixelInputType, typename T_PixelOutputType>
	void SubtractImageStack( const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack, std::shared_ptr < stk::Image<T_PixelOutputType> > result );


};

}

#include "stkImageSubtract.hxx"


#endif /* __stkImageSubtract_h */

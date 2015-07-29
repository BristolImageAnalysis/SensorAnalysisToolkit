/*
 * stkImageVariance.h
 *
 *  Created on: 15 Jul 2015
 *      Author: lewish
 */
#ifndef __stkImageVariance_h
#define __stkImageVariance_h

#include "stkImage.h"
#include "stkImageStack.h"
#include "stkImageDivision.h"
#include "tbb/tbb.h"


namespace stk{
/**
 * \class ImageVariance
 * \brief ImageVariance class calculates the variance using the dark stack and pedestal image.
 *
 * ImageVariance class subtracts the pedestal image from each frame of the dark stack and then squares. The variance for each frame of the stack is put in an output file and then divided by the number of images in stack.
 */

class ImageVariance{

public:

	/**
	 * Default constructor.
	 */
	ImageVariance();
	/**
	* Deconstrutor
	*
	*/
	virtual ~ ImageVariance();
	/**
	 * Function to remove the pedestal from each frame in the stack, square them and sum into a final image.
	 * @par[in] imagestack The dark image stack.
	 * @par[in] pedestal The pedestal image.
	 * @par[in] result The ouput variance image.
	 */
	template< typename T_PixelInputType, typename T_PixelOutputType>
	void VarianceImageStack(const std::shared_ptr<stk::ImageStack<T_PixelInputType> > imagestack, const  std::shared_ptr<stk::Image<T_PixelOutputType> > pedestal, std::shared_ptr<stk::Image<T_PixelOutputType> > result );



};

}

#include "stkImageVariance.hxx"

#endif /* __stkImageVariance_h */

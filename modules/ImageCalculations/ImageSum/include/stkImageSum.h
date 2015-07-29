/*====================================
 * stkImageSum.h
 *
 *  Created on: 8 Jun 2015
 *      Author: phrfp
 *==================================*/

#ifndef __stkImageSum_h
#define __stkImageSum_h

#include "stkImage.h"
#include "stkImageStack.h"
#include "tbb/tbb.h"
/**
 * \class ImageSum
 * \brief Class to take a stack of images sum them and write the result to a image.
 *
 * Loops over all the elements in the image stack computes the sum and writes the result to a image. The stack images must be the same size as the image to written too. The pixel size of the both
 * stack and image must also be the same.
 */
namespace stk{

//template <typename T_Pixeldata>
class ImageSum{
public:
	/**
	 * Defualt constructor
	 */
	ImageSum();
	/**
	 * Defualt destructor
	 */
	virtual ~ImageSum();

	/**
	 * Function that sums pixels across an image stack and writes the sum into an new image. For example for two 2x2 images [1 2], [3 4] and [5 6], [7 8] the result would be [6 8], [10 12]. Differs from
	 * SumImageStack in the implementation. It uses the stL transform and plus functor to do the summation over the image stack
	 * @par[in] imageStack Shared pointer to the image stack to be summed
	 * @par[in] result Shared pointer to the image where the sum is to written
	 */
	template< typename T_PixelInputType, typename T_PixelOutputType>
	void SumImageStack( const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack, std::shared_ptr < stk::Image<T_PixelOutputType> > result );
};

}
#include "stkImageSum.hxx"


#endif /* __stkImageSum_h */

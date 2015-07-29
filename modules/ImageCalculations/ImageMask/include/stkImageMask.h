/*
 * stkImageMask.h
 *
 *  Created on: 16 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageMask_h
#define __stkImageMask_h

#include "stkImage.h"

namespace stk{


class ImageMask{

	/**
	 * \class ImageMask
	 * \brief ImageMask class takes input image, pedestal image and gain map to produce a mask of bad pixel locations.
	 *
	 * ImageMask class takes creates a mask of bad pixel locations using user input thresholds. Thresholds on the pedestal and variance value can be changed. Pixels with a gain of 0 are taken as bad pixels.
	 */

public:

	/**
	 * Default constructor
	 */
	ImageMask();
	/**
	 * Default Destructor
	 */
	virtual ~ImageMask();
	/**
	 * Function to create a mask of bad pixel locations. The user can specify upper and lower bound thresholds for the accepted values of the pedestal and variance image. If the gain is 0 the function assumes it is a bad pixel as the thresholds for gain are set in the flat field correction class.
	 * @par[in] imageStack The input stack of images.
	 * @par[in] varianceImage The variance image input.
	 * @par[in] maskingImage The masking image output.
	 * @par[in] pedImage The pedestal image.
	 * @par[in] gainMap The gain map of the sensor.
	 * @par[in] threshup The upper threshold for variance values.
	 * @par[in] threshdown The lower threshold for variance values.
	 * @par[in] pedThreshUp The upper threshold for pedestal values.
	 * @par[in] pedThreshDown The lower threshold for pedestal values.
	 */

	template< typename T_PixelInputType, typename T_PixelOutputType>
	void MaskImage(const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack,const std::shared_ptr< stk::Image<T_PixelOutputType> > varianceImage, std::shared_ptr< stk::Image<bool> > maskingImage,  std::shared_ptr< stk::Image<T_PixelOutputType> > pedImage, std::shared_ptr< stk::Image<T_PixelOutputType> > gainMap, int threshup, int threshdown, int pedThreshUp, int pedThreshDown);
	/**
	 * Function to create a mask of bad pixel locations. Instead of outputting a bool image, an integer image is produced. Only used for testing.
	 */
	template< typename T_PixelInputType, typename T_PixelOutputType>
	void MaskImage(const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack,const std::shared_ptr< stk::Image<T_PixelOutputType> > varianceImage, std::shared_ptr< stk::Image<T_PixelOutputType> > maskingImage,  std::shared_ptr< stk::Image<T_PixelOutputType> > pedImage,std::shared_ptr< stk::Image<T_PixelOutputType> > gainMap, int threshup, int threshdown, int pedThreshUp, int pedThreshDown);
	/**
		 * Function to create a mask of bad pixel locations. The user can specify upper and lower bound thresholds for the accepted values of the pedestal and variance image. If the gain is 0 the function assumes it is a bad pixel as the thresholds for gain are set in the flat field correction class.
		 * @par[in] imageInput The input image.
		 * @par[in] varianceImage The variance image input.
		 * @par[in] maskingImage The masking image output.
		 * @par[in] pedImage The pedestal image.
		 * @par[in] gainMap The gain map of the sensor.
		 * @par[in] threshup The upper threshold for variance values.
		 * @par[in] threshdown The lower threshold for variance values.
		 * @par[in] pedThreshUp The upper threshold for pedestal values.
		 * @par[in] pedThreshDown The lower threshold for pedestal values.
		 */
	template<typename T_PixelOutputType>
	void MaskImage(const std::shared_ptr< stk::Image<T_PixelOutputType> > imageInput,const std::shared_ptr< stk::Image<T_PixelOutputType> > varianceImage, std::shared_ptr< stk::Image<bool> > maskingImage,  std::shared_ptr< stk::Image<T_PixelOutputType> > pedImage, std::shared_ptr< stk::Image<T_PixelOutputType> > gainMap, int threshup, int threshdown, int pedThreshUp, int pedThreshDown);


};

}

#include "stkImageMask.hxx"

#endif /* __stkImageMask_h */

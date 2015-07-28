/*
 * stkImageResize.hxx
 *
 *  Created on: 21 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageResize_hxx
#define __stkImageResize_hxx


#include "stkImageResize.h"
#include <algorithm>
#include <functional>


namespace stk{


ImageResize::ImageResize(){}
ImageResize::~ImageResize(){}


template<typename T_PixelOutputType>
void ImageResize::ResizeImage(std::shared_ptr< stk::Image<T_PixelOutputType> > resizeImage, std::shared_ptr< stk::Image<T_PixelOutputType> > resultImage){

			int pix=0;
			for(int iElements=0; iElements<(resizeImage->NumberOfPixels()-4);iElements+=4)
			{
				T_PixelOutputType tempPixel=0;
				T_PixelOutputType count=0;
				//std::cout<<"iele"<<iElements<<std::endl;

				for(int iKernel=iElements; iKernel<(iElements+(4*resizeImage->NumberOfRows()));iKernel++){


					tempPixel += resizeImage->GetPixelAt(iKernel);
					count++;

					if(count==4)
					{
						iKernel=iKernel+(resizeImage->NumberOfRows()-4);
						count=0;

					}

				}

				resultImage->SetPixelAt(pix,tempPixel/16);

				pix++;
				if((iElements+4)%resizeImage->NumberOfRows()==0)
				{
						iElements+=(3*(resizeImage->NumberOfRows()));

				}
			}
}

}



#endif /* __stkImageResize_hxx */

/*
 * stkImageMask.hxx
 *
 *  Created on: 16 Jul 2015
 *      Author: lewish
 */

#ifndef __stkImageMask_hxx
#define __stkImageMask_hxx

#include "stkImageMask.h"
#include <algorithm>
#include <functional>


namespace stk{



 ImageMask::ImageMask(){}
 ImageMask::~ImageMask(){}







template<typename T_PixelInputType, typename T_PixelOutputType>
void ImageMask::MaskImage(std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack,std::shared_ptr< stk::Image<T_PixelOutputType> > varianceImage, std::shared_ptr< stk::Image<bool> > maskingImage, std::shared_ptr< stk::Image<T_PixelOutputType> > pedImage, std::shared_ptr< stk::Image<T_PixelOutputType> > gainMap, int threshup, int threshdown, int pedThreshUp, int pedThreshDown){


	for(int iFrames=0; iFrames<imageStack->NumberOfImageInStack();iFrames++){
		T_PixelOutputType count=0;
		for( int iElements=0; iElements < maskingImage->NumberOfPixels(); iElements++ ){

			T_PixelInputType tempStack = imageStack->GetPixelAt(iFrames*maskingImage->NumberOfPixels()+iElements);
			if(tempStack>5000){
				maskingImage->SetPixelAt(iElements, true);
				count++;
									//std::cout<<tempStack<<std::endl;
			}
			else{
				maskingImage->SetPixelAt(iElements, false);
			}
		}
	}






	T_PixelOutputType count3=0;

		for( int iElements=0; iElements < varianceImage->NumberOfPixels(); iElements++ )
		{//loop over all the pixels in the result
			T_PixelOutputType tempPixel = varianceImage->GetPixelAt( iElements); //get stack value
			T_PixelOutputType tempPedPixel = pedImage->GetPixelAt( iElements );

			//||tempPedPixel>pedThreshUp||tempPedPixel<pedThreshDown
				if(tempPixel>threshup||tempPixel<threshdown||tempPedPixel>pedThreshUp||tempPedPixel<pedThreshDown||gainMap->GetPixelAt(iElements)==0){

						maskingImage->SetPixelAt( iElements,true);
						count3++;
						std::cout<<count3/varianceImage->NumberOfPixels()<<std::endl;
					}


		}
}



template<typename T_PixelInputType, typename T_PixelOutputType>
void ImageMask::MaskImage(std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack,std::shared_ptr< stk::Image<T_PixelOutputType> > varianceImage, std::shared_ptr< stk::Image<T_PixelOutputType> > maskingImage, std::shared_ptr< stk::Image<T_PixelOutputType> > pedImage, std::shared_ptr< stk::Image<T_PixelOutputType> > gainMap, int threshup, int threshdown, int pedThreshUp, int pedThreshDown){


	for(int iFrames=0; iFrames<imageStack->NumberOfImageInStack();iFrames++){
		T_PixelOutputType count=0;
		for( int iElements=0; iElements < maskingImage->NumberOfPixels(); iElements++ ){

			T_PixelInputType tempStack = imageStack->GetPixelAt(iFrames*maskingImage->NumberOfPixels()+iElements);
			if(tempStack>9000){
				maskingImage->SetPixelAt(iElements, 255);
				count++;
									//std::cout<<tempStack<<std::endl;
			}
			else{
				maskingImage->SetPixelAt(iElements, 0);
			}
		}
	}






	T_PixelOutputType count3=0;

		for( int iElements=0; iElements < varianceImage->NumberOfPixels(); iElements++ )
		{//loop over all the pixels in the result
			T_PixelOutputType tempPixel = varianceImage->GetPixelAt( iElements); //get stack value
			T_PixelOutputType tempPedPixel = pedImage->GetPixelAt( iElements );

			//||tempPedPixel>pedThreshUp||tempPedPixel<pedThreshDown
				if(tempPixel>threshup||tempPixel<threshdown||tempPedPixel>pedThreshUp||tempPedPixel<pedThreshDown){

						maskingImage->SetPixelAt( iElements,255);
						count3++;
						//std::cout<<count3/varianceImage->NumberOfPixels()<<std::endl;
					}


		}
}



template<typename T_PixelOutputType>
void ImageMask::MaskImage(std::shared_ptr< stk::Image<T_PixelOutputType> > imageInput,std::shared_ptr< stk::Image<T_PixelOutputType> > varianceImage, std::shared_ptr< stk::Image<bool> > maskingImage, std::shared_ptr< stk::Image<T_PixelOutputType> > pedImage, std::shared_ptr< stk::Image<T_PixelOutputType> > gainMap, int threshup, int threshdown, int pedThreshUp, int pedThreshDown){






	T_PixelOutputType count=0;
for(int iElements=0; iElements<varianceImage->NumberOfPixels(); iElements++)

			{//loop over all the pixels in the result
			T_PixelOutputType tempPixel = varianceImage->GetPixelAt( iElements); //get stack value
			T_PixelOutputType tempPedPixel = pedImage->GetPixelAt( iElements );


				if(tempPixel>threshup||tempPixel<threshdown||tempPedPixel>pedThreshUp||tempPedPixel<pedThreshDown||gainMap->GetPixelAt(iElements)==0){

						maskingImage->SetPixelAt( iElements,true);
						count++;

					}
				else{
					maskingImage->SetPixelAt(iElements, false);

				}


		}
		std::cout<<"Percentage bad: "<<(count/varianceImage->NumberOfPixels())*100<<"%"<<std::endl;
}


}



#endif /* __stkImageMask_hxx */

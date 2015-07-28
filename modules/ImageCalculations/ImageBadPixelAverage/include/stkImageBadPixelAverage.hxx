/*
 * stkImageBadPixelAverage.hxx
 *
 *  Created on: 17 Jul 2015
 *      Author: lewish
 */



#ifndef __stkImageBadPixelAverage_hxx
#define __stkImageBadPixelAverage_hxx


#include "stkImageBadPixelAverage.h"
#include <algorithm>
#include <functional>
#include <vector>



namespace stk{

ImageBadPixelAverage::ImageBadPixelAverage(){}
ImageBadPixelAverage::~ImageBadPixelAverage(){}





template< typename T_PixelInputType>
 void ImageBadPixelAverage::BadPixelAverage(const std::shared_ptr< stk::ImageStack<T_PixelInputType> > imageStack, std::shared_ptr< stk::Image<bool> > maskingImage){







			tbb::parallel_for(0, imageStack->NumberOfImageInStack(), [&](int iFrames)
			//for(int iFrames=0; iFrames < imageStack->NumberOfImageInStack(); iFrames++)
			{//loop all frames of image stack



								//std::cout<<"iFrames "<<iFrames<<std::endl;
								//for	(int iElements=0; iElements < maskingImage->NumberOfPixels(); iElements++)//loop all pixels of each image in stack using size of mask image.
								tbb::parallel_for(0, maskingImage->NumberOfPixels(), [&](int iElements){
									//std::cout<<"iElements "<<iElements<<std::endl;
									//std::vector<T_Pixeldata> kernel;
									bool tempPed = maskingImage->GetPixelAt(iElements);
									//std::cout<<tempPed<<std::endl;
									if(tempPed==true)
									{//Checking mask details, true for bad pixel.
										float buffAvg=0;
										float divisor=0;
										//std::cout<<"before"<<imageStack->GetPixelAt((iFrames*maskingImage->NumberOfPixels()) + iElements)<<std::endl;


											int y=0;
										for(int iTest = ((iFrames*maskingImage->NumberOfPixels()) + ((iElements - maskingImage->NumberOfColumns())-1)); iTest < (iFrames*maskingImage->NumberOfPixels()) + iElements + maskingImage->NumberOfColumns()+2; iTest++)
										{	//std::cout<<"iTest="<<iTest<<std::endl;
											y++;
										if(iTest>=(iFrames*maskingImage->NumberOfPixels())&&iTest<((iFrames+1)*maskingImage->NumberOfPixels())&&iTest!=iElements-(iFrames*maskingImage->NumberOfPixels())&&maskingImage->GetPixelAt(iTest-(iFrames*maskingImage->NumberOfPixels()))!=true)
										{

											//std::cout<<"next if"<<std::endl;
											buffAvg+=imageStack->GetPixelAt(iTest);
											divisor++;
										std::cout<<"tot-div "<<buffAvg<<" "<<divisor<<" "<<y<<maskingImage->GetPixelAt(iTest-(iFrames*maskingImage->NumberOfPixels()))<<std::endl;

										}


										if(iTest==((iFrames*maskingImage->NumberOfPixels()) + (iElements - maskingImage->NumberOfColumns())+1)||iTest==(iFrames*maskingImage->NumberOfPixels()) + (iElements+1))
										{
											//std::cout<<"before dropping line "<<iTest<<std::endl;

											iTest=(iTest+(maskingImage->NumberOfColumns()))-3;
											//std::cout<<"after dropping line "<<iTest<<std::endl;
										}
										//std::cout<<"oiut"<<std::endl;
									}

										std::cout<<buffAvg/divisor<<"pixel "<<iElements<<std::endl;

										imageStack->SetPixelAt(((iFrames*maskingImage->NumberOfPixels()) + iElements),(buffAvg/divisor));

								}
							});
				} );




}




template< typename T_PixelOutputType>
 void ImageBadPixelAverage::BadPixelAverage(const std::shared_ptr< stk::Image<T_PixelOutputType> > imageInput, std::shared_ptr< stk::Image<bool> > maskingImage){





	//std::cout<<"shsj"<<std::endl;



								for	(int iElements=0; iElements < maskingImage->NumberOfPixels(); iElements++)//loop all pixels of each image in stack using size of mask image.
									//tbb::parallel_for(0, maskingImage->NumberOfPixels(), [&](int iElements)
									{

									bool tempPed = maskingImage->GetPixelAt(iElements);
									//std::cout<<tempPed<<std::endl;
									if(tempPed==true)
									{//Checking mask details, true for bad pixel.
										float buffAvg=0;
										float divisor=0;

										//std::cout<<"shsj"<<std::endl;
											int y=0;
										for(int iTest = ((iElements - maskingImage->NumberOfColumns())-1); iTest <  iElements + maskingImage->NumberOfColumns()+2; iTest++)
										{	//std::cout<<"iTest="<<iTest<<" "<<iElements<<std::endl;
											y++;
										if(iTest>=0&&iTest<maskingImage->NumberOfPixels()&&iTest!=iElements&&maskingImage->GetPixelAt(iTest)!=true)
											{

											//std::cout<<"next if"<<std::endl;
											buffAvg+=imageInput->GetPixelAt(iTest);
											divisor++;
										//std::cout<<"tot-div "<<buffAvg<<" "<<divisor<<" "<<iTest<<" "<<maskingImage->GetPixelAt(iElements)<<std::endl;

										}


										if(iTest==( (iElements - maskingImage->NumberOfColumns())+1)||iTest == (iElements+1))
										{
											//std::cout<<"before dropping line "<<iTest<<std::endl;

											iTest=(iTest+(maskingImage->NumberOfColumns()))-3;
											//std::cout<<"after dropping line "<<iTest<<std::endl;
										}
										//std::cout<<"oiut"<<std::endl;
									}

										//std::cout<<buffAvg/divisor<<"pixel "<<iElements<<std::endl;

										imageInput->SetPixelAt(iElements,(buffAvg/divisor));
										maskingImage->SetPixelAt(iElements, false);
										//std::cout<<imageInput->GetPixelAt(iElements)<<std::endl;

								}
							}





}

}




#endif /* __stkImageBadPixelAverage_h */

/*
 * stkImageMaskTest.cxx
 *
 *  Created on: 16 Jul 2015
 *      Author: lewish
 */




/*
 * stkImageUnitTest.cxx
 *
 *  Created on: 2 Jun 2015
 *      Author: phrfp
 */



#include <iostream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "stkImageStack.h"
#include "stkImage.h"
#include "stkImageMask.h"



/**
 * Tests to check that the ImageDivision class is operating correctly
 */

/**
 * Create a set of test images and compute the division
 */


TEST( ImageMask, CheckImageMask ){

	// 2  4  6  8 => 2x2 image 1

	//Crate simple test image
	std::shared_ptr< std::vector<float> > testbuffer(new std::vector<float>( ) );
	unsigned short testValue =4;


	for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){
		if(iBuffer==1)
				{
					testbuffer->push_back(testValue);
				}
		else{
		testbuffer->push_back(0);
		}

	}


	std::shared_ptr< std::vector<bool> > maskbuffer(new std::vector<bool>( ) );
		for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){

				maskbuffer->push_back(false);

		}

	std::shared_ptr<stk::Image<bool> > maskImage(new stk::Image<bool>);
	maskImage->Initialise(maskbuffer,2,2);//initialises mask image

	std::shared_ptr<stk::Image<float> > myImage(new stk::Image<float>);
	myImage->Initialise( testbuffer, 2, 2 ); //initialise to 2x2 image

	std::shared_ptr<stk::Image<float> > varianceImage(new stk::Image<float>);
	myImage->Initialise( testbuffer, 2, 2 ); //initialise to 2x2 image

	std::shared_ptr<stk::Image<float> > myPed(new stk::Image<float>);
	myImage->Initialise( testbuffer, 2, 2 ); //initialise to 2x2 image

	std::shared_ptr<stk::Image<float> > myGain(new stk::Image<float>);
	myImage->Initialise( testbuffer, 2, 2 ); //initialise to 2x2 image


	stk::ImageMask myMask;//create divider
	int thresh=2;
	myMask.MaskImage( myImage, varianceImage, maskImage, myPed, myGain, thresh , 2, 3, 4);//perform the division

	for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){
			if(iBuffer==0) EXPECT_FALSE ( maskImage->GetPixelAt( iBuffer ) ); //check each element
			if(iBuffer==1) EXPECT_TRUE ( maskImage->GetPixelAt( iBuffer ) ); //
			if(iBuffer==2) EXPECT_FALSE ( maskImage->GetPixelAt( iBuffer )); //
			if(iBuffer==3) EXPECT_FALSE ( maskImage->GetPixelAt( iBuffer )); //
		}




}







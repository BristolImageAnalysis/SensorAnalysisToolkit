/*
 * stkImageResizeTest.cxx
 *
 *  Created on: 21 Jul 2015
 *      Author: lewish
 */




#include <iostream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "stkImageStack.h"
#include "stkImage.h"
#include "stkImageResize.h"


/**
 * Tests to check that the ImageMinus class is operating correctly
 */

/**
 * Create a set of test images and compute the sum
 */
TEST( ImageResize, CheckResize){

	// 1   2  3  4 => 2x2 image 1
	// 5   6  7  8 => 2x2 image 2
	// 9  10 11 12 => 2x2 image 3
	// 13 14 15 16 => 2x2 image 4
	//------------
	// 28 32 36 40 => Sum
	//Crate simple test image
	std::shared_ptr< std::vector<float> > testbuffer(new std::vector<float>( ) );
	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 64; iBuffer++ ){




		if(iBuffer==5||iBuffer==7||iBuffer==36||iBuffer==9||iBuffer==11){
			testbuffer->push_back(5);
		}
		testbuffer->push_back(0);
		testValue++;


	}
	///

	std::shared_ptr<stk::Image<float> > myImage(new stk::Image<float>);
	myImage->Initialise( testbuffer, 8, 8 ); //initialise to 2 images 2x2



	std::shared_ptr< std::vector<float> > maskbuffer(new std::vector<float>( ) );
	unsigned short testPed =1;
		for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){

				maskbuffer->push_back(0);


		}
	std::shared_ptr<stk::Image<float> > myMask( new stk::Image<float>(2,2) );//non-default to create initialised buffer
	myMask->Initialise(maskbuffer,2,2);

	stk::ImageResize myResizer;
	myResizer.ResizeImage( myImage, myMask );//sum using the STL iterator method



	for( int iBuffer = 0; iBuffer < 8; iBuffer++ ){
		if(iBuffer==0) EXPECT_EQ ( myMask->GetPixelAt( iBuffer ), 14 ); //check each element
		if(iBuffer==1) EXPECT_EQ ( myMask->GetPixelAt( iBuffer ), 18); //
		if(iBuffer==2) EXPECT_EQ ( myMask->GetPixelAt( iBuffer ), 46 ); //
		if(iBuffer==3) EXPECT_EQ ( myMask->GetPixelAt( iBuffer ), 50 ); //




	}

}

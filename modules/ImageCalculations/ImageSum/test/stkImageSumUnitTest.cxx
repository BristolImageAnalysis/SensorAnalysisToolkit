/*
 * stkImageSumUnitTest.cxx
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
#include "stkImageSum.h"


/**
 * Tests to check that the ImageSum class is operating correctly
 */

/**
 * Create a set of test images and compute the sum
 */
TEST( ImageSum, CheckAdditionOfArray ){

	// 1   2  3  4 => 2x2 image 1
	// 5   6  7  8 => 2x2 image 2
	// 9  10 11 12 => 2x2 image 3
	// 13 14 15 16 => 2x2 image 4
	//------------
	// 28 32 36 40 => Sum
	//Crate simple test image
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( ) );
	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->push_back(65534);
		testValue++;

	}
	///

	std::shared_ptr<stk::ImageStack<unsigned short> > myImageStack(new stk::ImageStack<unsigned short>);
	myImageStack->Initialise( testbuffer, 4, 2, 2 ); //initialise to 4 images 2x2

	std::shared_ptr<stk::Image<float> > myImage( new stk::Image<float>(2,2) );//non-default to create initialised buffer

	stk::ImageSum mySummer;
	mySummer.SumImageStack( myImageStack, myImage );//sum using the STL iterator method

	for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){
		if(iBuffer==0) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 262136 ); //check each element
		if(iBuffer==1) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 262136 ); //
		if(iBuffer==2) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 262136 ); //
		if(iBuffer==3) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 262136 ); //
	}

}







/*
 * stkImageSubractTest.cxx
 *
 *  Created on: 14 Jul 2015
 *      Author: lewish
 */



#include <iostream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "stkImageStack.h"
#include "stkImage.h"
#include "stkImageSubtract.h"


/**
 * Tests to check that the ImageSubtract class is operating correctly
 */

/**
 * Create a set of test images and compute the subtraction
 */
TEST( ImageSubtract, CheckSubractionOfArray ){

	// 1   2  3  4 => 2x2 image 1
	// 5   6  7  8 => 2x2 image 2

	//------------
	// -4 -4 -4 -4 => Subtraction
	//Create simple test image
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( ) );
	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->push_back(testValue);
		testValue++;

	}
	///

	std::shared_ptr<stk::ImageStack<unsigned short> > myImageStack(new stk::ImageStack<unsigned short>);
	myImageStack->Initialise( testbuffer, 4, 2, 2 ); //initialise to 2 images 2x2

	std::shared_ptr<stk::Image<float> > myImage( new stk::Image<float>(2,2) );//non-default to create initialised buffer

	stk::ImageSubtract mySubtract;
	mySubtract.SubtractImageStack( myImageStack, myImage );//subtract using the STL iterator method

	for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){
		if(iBuffer==0) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 4 ); //check each element
		if(iBuffer==1) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 4 ); //
		if(iBuffer==2) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 4 );
		if(iBuffer==3) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 4 );
	}

}




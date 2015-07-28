/*
 * stkImageVarianceTest.cxx
 *
 *  Created on: 15 Jul 2015
 *      Author: lewish
 */




#include <iostream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "stkImageStack.h"
#include "stkImage.h"
#include "stkImageVariance.h"


/**
 * Tests to check that the ImageVariance class is operating correctly
 */

/**
 * Create a set of test images and compute the sum
 */
TEST( ImageVariance, CheckVariance ){

	// 1   2  3  4 => 2x2 image 1
	// 5   6  7  8 => 2x2 image 2
	// 9  10 11 12 => 2x2 image 3
	// 13 14 15 16 => 2x2 image 4
	//------------
	// 28 32 36 40 => Sum
	//Crate simple test image
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( ) );
	unsigned short testValue =2;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->push_back(testValue);
		testValue++;

	}
	///

	std::shared_ptr<stk::ImageStack<unsigned short> > myImageStack(new stk::ImageStack<unsigned short>);
	myImageStack->Initialise( testbuffer, 4, 2, 2 ); //initialise to 4 images 2x2

	std::shared_ptr<stk::Image<float> > myImage( new stk::Image<float>(2,2) );//non-default to create initialised buffer


	std::shared_ptr< std::vector<float> > pedtestbuffer(new std::vector<float>( ) );
	for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){

			pedtestbuffer->push_back(1);

		}

	std::shared_ptr<stk::Image<float> > myPed( new stk::Image<float>(2,2) );
	myPed->Initialise(pedtestbuffer,2,2);

	stk::ImageVariance myVariance;
	myVariance.VarianceImageStack( myImageStack, myPed, myImage );//Variance Calc

	for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){
		if(iBuffer==0) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 1 ); //check each element
		if(iBuffer==1) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 4 ); //
		if(iBuffer==2) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 9 ); //
		if(iBuffer==3) EXPECT_EQ ( myImage->GetPixelAt( iBuffer ), 16); //
	}

}

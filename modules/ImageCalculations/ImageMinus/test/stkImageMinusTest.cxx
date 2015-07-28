/*

 * stkImageMinusTest.cxx
 *
 *  Created on: 17 Jul 2015
 *      Author: lewish
 */



#include <iostream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "stkImageStack.h"
#include "stkImage.h"
#include "stkImageMinus.h"


/**
 * Tests to check that the ImageMinus class is operating correctly
 */

/**
 * Create a set of test images and compute the sum
 */
TEST( ImageMinus, CheckRemove){

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

		testbuffer->push_back(testValue);
		testValue++;

	}
	///

	std::shared_ptr<stk::ImageStack<unsigned short> > myImageStack(new stk::ImageStack<unsigned short>);
	myImageStack->Initialise( testbuffer, 4, 2, 2 ); //initialise to 4 images 2x2



	std::shared_ptr< std::vector<float> > pedbuffer(new std::vector<float>( ) );
unsigned short testPed =1;
		for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){

			pedbuffer->push_back(1);
			testPed++;


		}
	std::shared_ptr<stk::Image<float> > myPed( new stk::Image<float>(2,2) );//non-default to create initialised buffer
	myPed->Initialise(pedbuffer,2,2);
	std::shared_ptr<stk::Image<float> > myOut( new stk::Image<float>(2,2) );

	stk::ImageMinus myMinus;
	myMinus.MinusImage( myImageStack, myPed, myOut );//sum using the STL iterator method

	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){
		if(iBuffer==0) EXPECT_EQ ( myOut->GetPixelAt( iBuffer ), 24 ); //check each element
		if(iBuffer==1) EXPECT_EQ ( myOut->GetPixelAt( iBuffer ), 28 ); //
		if(iBuffer==2) EXPECT_EQ ( myOut->GetPixelAt( iBuffer ), 32); //
		if(iBuffer==3) EXPECT_EQ ( myOut->GetPixelAt( iBuffer ), 36); //

	}

}



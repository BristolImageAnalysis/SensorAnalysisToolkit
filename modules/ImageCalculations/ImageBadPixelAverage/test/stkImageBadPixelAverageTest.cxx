/*
 * stkImageBadPixelAverage.cxx
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
#include "stkImageBadPixelAverage.h"


/**
 * Tests to check that the ImageMinus class is operating correctly
 */

/**
 * Create a set of test images and compute the sum
 */
TEST( ImageBadPixelAverage, CheckAverage){

	// 1   2  3  4 => 2x2 image 1
	// 5   6  7  8 => 2x2 image 2
	// 9  10 11 12 => 2x2 image 3
	// 13 14 15 16 => 2x2 image 4
	//------------
	// 28 32 36 40 => Sum
	//Crate simple test image
	std::shared_ptr< std::vector<float> > testbuffer(new std::vector<float>( ) );
	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 25; iBuffer++ ){


		if(iBuffer==0){
			testbuffer->push_back(50);
		}
		else
		{
			testbuffer->push_back(0);
		}
		testValue++;


	}
	///

	std::shared_ptr<stk::Image<float> > myImageStack(new stk::Image<float>());
	myImageStack->Initialise( testbuffer, 5, 5 ); //initialise to 2 images 2x2



	std::shared_ptr< std::vector<bool> > maskbuffer(new std::vector<bool>( ) );
	unsigned short testPed =1;
		for( int iBuffer = 0; iBuffer < 25; iBuffer++ ){

				if(iBuffer!=0){
						maskbuffer->push_back(true);
				}
				else{
					maskbuffer->push_back(false);
				}


		}
	std::shared_ptr<stk::Image<bool> > myMask( new stk::Image<bool>(5,5) );//non-default to create initialised buffer
	myMask->Initialise(maskbuffer,5,5);

	stk::ImageBadPixelAverage myAverage;
	myAverage.BadPixelAverage( myImageStack, myMask );//sum using the STL iterator method


	for (int iBuffer =0; iBuffer<16; iBuffer++){
		if(iBuffer==0) EXPECT_FALSE (myMask->GetPixelAt(iBuffer));
		if(iBuffer==1) EXPECT_FALSE (myMask->GetPixelAt(iBuffer));
		if(iBuffer==2) EXPECT_FALSE (myMask->GetPixelAt(iBuffer));
		if(iBuffer==3) EXPECT_FALSE (myMask->GetPixelAt(iBuffer));
		if(iBuffer==4) EXPECT_FALSE (myMask->GetPixelAt(iBuffer));
		if(iBuffer==5) EXPECT_FALSE (myMask->GetPixelAt(iBuffer));
		if(iBuffer==6) EXPECT_FALSE (myMask->GetPixelAt(iBuffer));
		if(iBuffer==7) EXPECT_TRUE (myMask->GetPixelAt(iBuffer));

	}
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){
		if(iBuffer==0) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 1 ); //check each element
		if(iBuffer==1) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 2 ); //
		if(iBuffer==2) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 3 ); //
		if(iBuffer==3) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 4 ); //
		if(iBuffer==4) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 5); //check each element
		if(iBuffer==5) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 6); //
		if(iBuffer==6) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 7); //
		if(iBuffer==7) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 8 );
		if(iBuffer==13) EXPECT_EQ ( myImageStack->GetPixelAt( iBuffer ), 12 );//


	}

}


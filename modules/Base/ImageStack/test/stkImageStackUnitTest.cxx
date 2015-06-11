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


/**
 * Tests to check that the ImageStack class is operating correctly
 */

/**
 * The first test uses a unitialised vector to check use count.
 */

TEST( ImageStack, CheckInitialiseNullBuffer ){

	std::shared_ptr< std::vector<unsigned short> > zeroBuffer;
	EXPECT_EQ( zeroBuffer.use_count(), 0 ); //test Null array

	std::unique_ptr<stk::ImageStack<unsigned short> > myImageStack(new stk::ImageStack<unsigned short>); //create stk image
	myImageStack->Initialise( zeroBuffer, 2, 2, 2 );//initialse image to buffer
	EXPECT_EQ( zeroBuffer.use_count(), 0 ); //test Null array

}

/**
 * Second test has an initialised vector used to check that the image stack points at it and release it when its finished
 */
TEST( ImageStack, CheckInitialiseInitBuffer ){

	std::shared_ptr< std::vector<unsigned short> > testNullArray(new std::vector<unsigned short> );
	EXPECT_EQ( testNullArray.use_count(), 1 ); //test use count on vector should be 1

	std::unique_ptr<stk::ImageStack<unsigned short> > myImageStack(new stk::ImageStack<unsigned short>);
	myImageStack->Initialise( testNullArray, 2, 2, 2 );
	EXPECT_EQ( testNullArray.use_count(), 2 ); //test that ImageStack now points at that buffer

	myImageStack.reset();
	EXPECT_EQ( testNullArray.use_count(), 1); //test that ImageStack no longer points at buffer


}

/**
 * Test the values returned by the iterator are correct.
 */
TEST( Image, CheckImageInitialised ){

	//Crate simple test image
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( ) );
	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->push_back(testValue);
		testValue++;

	}

	std::unique_ptr<stk::ImageStack<unsigned short> > myImageStack(new stk::ImageStack<unsigned short>);
	myImageStack->Initialise( testbuffer, 4, 2, 2 ); //initialise to 4 images 2x2

	std::vector<unsigned short>::iterator startOfFrame_0 = myImageStack->StartOfFrame(0);
	EXPECT_EQ( (*startOfFrame_0), testbuffer->front() ); //test that the iterator returned is the front of the test buffer

	std::vector<unsigned short>::iterator startOfFrame_1 = myImageStack->StartOfFrame(1);
	EXPECT_EQ( (*startOfFrame_1), 5 );//this is the 5th element in the array which is first pixel in the second image

	std::vector<unsigned short>::iterator startOfFrame_2 = myImageStack->StartOfFrame(2);
	EXPECT_EQ( (*startOfFrame_2), 9 );

	std::vector<unsigned short>::iterator startOfFrame_3 = myImageStack->StartOfFrame(3);
	EXPECT_EQ( (*startOfFrame_3), 13 );

	std::vector<unsigned short>::iterator endOfFrame_3 = myImageStack->EndOfFrame(3);
	EXPECT_EQ( (*endOfFrame_3), 16 ); //check last pixel in last image


}








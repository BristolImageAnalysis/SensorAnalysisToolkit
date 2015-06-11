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
#include "stkImage.h"


/**
 * Set of tests to check that Image class is working correctly
 */

/**
 * First check: Non-initialised vector does not increase the use_count
 */
TEST( Image, CheckInitialiseNullBuffer ){

	std::shared_ptr< std::vector<unsigned short> > zeroBuffer;
	EXPECT_EQ( zeroBuffer.use_count(), 0 ); //test Null array

	std::unique_ptr<stk::Image<unsigned short> > myImage(new stk::Image<unsigned short>); //create stk image
	myImage->Initialise( zeroBuffer, 2, 3 );//initialse image to buffer
	EXPECT_EQ( zeroBuffer.use_count(), 0 ); //test Null array

}

/**
 * Second check: Non-Default constructor creates the vector to store pixel data correctly
 */
TEST( Image, CheckImageNonDefaultConstructor ){


	std::unique_ptr<stk::Image<unsigned short> > myImage(new stk::Image<unsigned short>(2,2) );

	EXPECT_EQ(myImage->SizeInBytes(), 8);//4 elements each 2 bytes
	EXPECT_EQ(myImage->ImageSize(), 4 );//check size is correct


}

/**
 * Third check: Check initialised vector is set initialised in the Image using the use_count of the shared pointer
 */
TEST( Image, CheckInitialiseInitBuffer ){

	std::shared_ptr< std::vector<unsigned short> > testNullArray(new std::vector<unsigned short> );
	EXPECT_EQ( testNullArray.use_count(), 1 ); //test Null array

	std::unique_ptr<stk::Image<unsigned short> > myImage(new stk::Image<unsigned short>);
	myImage->Initialise( testNullArray, 2, 3 );
	EXPECT_EQ( testNullArray.use_count(), 2 ); //test that myImage now points at that buffer.
	EXPECT_EQ(myImage->SizeInBytes(), 0);//size should be 0 as no elements have been written to.

}

/**
 * Fourth check: Check initialised vector with values in has correct number and size
 */
TEST( Image, CheckImageInitialised ){

	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( 16,25 ) );

	std::unique_ptr<stk::Image<unsigned short> > myImage(new stk::Image<unsigned short>);
	myImage->Initialise( testbuffer, 4, 4 );
	EXPECT_EQ(myImage->SizeInBytes(), 32);//16 elements each 2 bytes
	EXPECT_EQ(myImage->ImageSize(), 16 );


}
/**
 * Fifth check: Check access memeber functions work correctly
 */

TEST( Image, CheckAccessMethods){

	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( ) );
	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->push_back(testValue);
		testValue++;

	}//Create test vector

	std::unique_ptr<stk::Image<unsigned short> > myImage(new stk::Image<unsigned short>);
	myImage->Initialise( testbuffer, 4, 4 );//set image to point to testbuffer

	testValue =1;
	for(int iBuffer = 0; iBuffer < myImage->NumberOfPixels(); iBuffer++){
		EXPECT_EQ( myImage->GetPixelAt(iBuffer), testValue );//access element using 1D method and chcek value is as set
		testValue++;

	}

	testValue =1;
	for(int irow=0; irow < myImage->NumberOfRows(); irow++){
		for(int icol=0; icol < myImage->NumberOfColumns(); icol++){
			EXPECT_EQ( myImage->GetPixelAt(irow,icol), testValue );//access element using row and col values
			testValue++;
		}
	}

	for(int irow=0; irow < myImage->NumberOfRows(); irow++){
		for(int icol=0; icol < myImage->NumberOfColumns(); icol++){
			myImage->SetPixelAt(irow,icol,1);//set all values to 1
		}
	}

	for(int irow=0; irow < myImage->NumberOfRows(); irow++){
		for(int icol=0; icol < myImage->NumberOfColumns(); icol++){
			EXPECT_EQ( myImage->GetPixelAt(irow,icol), 1 );//check that new vector is correct
		}
	}

	//test iterators
	for( std::vector<unsigned short>::iterator it=myImage->StartImage(); it != myImage->EndImage(); it++ )
		EXPECT_EQ( (*it), 1 );

}






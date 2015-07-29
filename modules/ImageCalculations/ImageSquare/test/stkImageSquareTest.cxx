/*
 * stkImageSquareTest.cxx
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
#include "stkImageSquare.h"



/**
 * Tests to check that the ImageDivision class is operating correctly
 */

/**
 * Create a set of test images and compute the division
 */


TEST( ImageSquare, CheckSquareOfArray ){

	// 2  4  6  8 => 2x2 image 1

	//Crate simple test image
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( ) );
	unsigned short testValue =2;
	for( int iBuffer = 0; iBuffer < 4; iBuffer++ ){

		testbuffer->push_back(testValue);
		testValue +=2;

	}
	///

	std::shared_ptr<stk::Image<unsigned short> > myImage(new stk::Image<unsigned short>);
	myImage->Initialise( testbuffer, 2, 2 ); //initialise to 2x2 image

	stk::ImageSquare<unsigned short> mySquarer;//create divider

	mySquarer.SquareImage( myImage );//perform the division

	for( std::vector<unsigned short>::iterator it = myImage->StartImage();
			it !=myImage->EndImage(); it++ ){//loop over pixels
		if(it==myImage->StartImage()) EXPECT_EQ( (*it), 4 );//check elements have correct values
		if(it==myImage->StartImage()+1) EXPECT_EQ( (*it), 16 );
		if(it==myImage->StartImage()+2) EXPECT_EQ( (*it), 36);
		if(it==myImage->StartImage()+3) EXPECT_EQ( (*it), 64 );

	}


}







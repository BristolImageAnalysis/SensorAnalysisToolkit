/*
 * stkRamImageIOUnitTest.cxx
 *
 *  Created on: 2 Jun 2015
 *      Author: phrfp
 */


#include <iostream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "stkRawImageStackIO.h"


/**
 * Tests to check that the IO stack class performs correctly.
 */

/**
 * The first test checks that the members are initialised correctly.
 */

TEST( RawIOImageStack, CheckConstructor ){

	std::unique_ptr<stk::IOImageStack<unsigned short> > myImageStackReader(new stk::IOImageStack<unsigned short>);//IO build according to pixel depth.


	EXPECT_EQ( myImageStackReader->NumberOfLoadedFrames(), 0); //should be 0 as no frames have been read
	EXPECT_EQ( myImageStackReader->MaximumBufferSize(), (unsigned)0);
	EXPECT_EQ( myImageStackReader->FramesLoaded() ,false);

}

/*
 * The second test opens and loads 6 images and checks that the correct number is loaded and the correct number of bytes have been loaded and that the flag has been set correctly.
 */

TEST( RawIOImageStack, CheckLoadingWithCorrectFile ){

	std::unique_ptr<stk::IOImageStack<unsigned short> > myImageStackReader(new stk::IOImageStack<unsigned short>);//IO build according to pixel depth.
	myImageStackReader->ReadImageStack( "/panfs/panasas01/phys/phrfp/SensorAnalysisToolKit/testing/data/", "testimage000%i.raw", 0, 6, 16777216 );

	int numberOfBytes = static_cast<int> (sizeof(unsigned short)*6*16777216);//pixel depth x num. of frames x frame size
	EXPECT_EQ( myImageStackReader->NumberOfLoadedFrames(), 6);
	EXPECT_EQ( myImageStackReader->NumberOfBytesLoaded(), numberOfBytes);
	EXPECT_EQ( myImageStackReader->FramesLoaded() ,true);

}

/*
 * Second test checks the elements have the correct value. This checks that the iterator is moving correctly between each read.
 */

TEST( RawIOImageStack, CheckLoadingStackValues ){

	std::unique_ptr<stk::IOImageStack<unsigned short> > myImageStackReader(new stk::IOImageStack<unsigned short>);//IO build according to pixel depth.
	std::shared_ptr< std::vector<unsigned short> > buffer = myImageStackReader->ReadImageStack( "/panfs/panasas01/phys/phrfp/SensorAnalysisToolKit/testing/data/", "testimage000%i.raw", 0, 6, 16777216 );


	EXPECT_EQ( buffer.use_count(), 1);//check counter has been decremented when returned from the IO reader

	EXPECT_EQ( buffer->front(), 25);//first pixel
	EXPECT_EQ( buffer->back(), 25);//last pixel in stack

	EXPECT_EQ( buffer->size(), ((unsigned int)16777216*6)); //check the vector size corresponds to the frame size

	std::vector<unsigned short>::iterator bufferIter = buffer->begin();
	bufferIter = bufferIter+16777216*4 +1; //first pixel in 4th frame;
	EXPECT_EQ( (*bufferIter), 25);

}

/*
 * Check that the class behaves correctly when the file name passed in not valid
 */

TEST( RawIOImageStack, CheckLoadingWithIncorrectFile ){

	std::unique_ptr<stk::IOImageStack<unsigned short> > myImageStackReader(new stk::IOImageStack<unsigned short>);//IO build according to pixel depth.
	myImageStackReader->ReadImageStack( "", "testimage000%i.raw", 0, 6, 16777216 );

	EXPECT_EQ( myImageStackReader->NumberOfLoadedFrames(), 0);
	EXPECT_EQ( myImageStackReader->NumberOfBytesLoaded(), 0);
	EXPECT_EQ( myImageStackReader->FramesLoaded() ,false);

}








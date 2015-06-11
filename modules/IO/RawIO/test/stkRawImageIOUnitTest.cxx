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
#include "stkRawImageIO.h"

/**
 * Unit tests to ensure that the image reader is working correctly for an image of 4096x4096 with 16bit pixels
 */

/**
 * First test ensures that if a correct image file is supplied then the image size is correct tested against the bytes loaded in by
 * the reader. Then that the first pixel is 25. The final check is that the
 * IO class has correcectly set the imageloaded input to true.
 */
TEST( RawIO, CheckFileLoadedWithGoodFile ){

	std::unique_ptr<stk::IO<unsigned short> > myImageReader(new stk::IO<unsigned short>);//IO build according to pixel depth.

	std::shared_ptr<std::vector<unsigned short> > myImage = myImageReader->ReadImage("/panfs/panasas01/phys/phrfp/SensorAnalysisToolKit/testing/data/testimage0000.raw");

	int imageSize = myImage->size();
	int byteRead =  myImageReader->BytesRead();

	EXPECT_EQ( myImageReader->ImageLoaded(), true);
	EXPECT_EQ( imageSize, byteRead);
	EXPECT_EQ( myImage->front() ,25);

}

/**
 * Second test are for if the file is not present so image size should be 0 as should be the number of bytes read. The second check is that
 * the image is empty and the final check is for the image loaded flag and that this is false.
 */

TEST( RawIO, CheckFileLoadedWithNoFile ){

	std::unique_ptr<stk::IO<unsigned short> > myImageReader(new stk::IO<unsigned short>);

	//Open Data file --> check that first element is 130
	std::shared_ptr<std::vector<unsigned short> > myImage = myImageReader->ReadImage("");

	int imageSize = myImage->size();
	int byteRead =  myImageReader->BytesRead();

	EXPECT_EQ( myImageReader->ImageLoaded() ,false);
	EXPECT_EQ( imageSize, byteRead);
	EXPECT_EQ( myImage->empty(), true);


}

TEST( RawIO, CheckFileReadAndWrite ){

	/** Have to use the image class to test writing the image  */
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>( ) );
	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->push_back(testValue);
		testValue++;

	}//Create test vector

	std::shared_ptr<stk::Image<unsigned short> > myImage(new stk::Image<unsigned short>);
	myImage->Initialise( testbuffer, 4, 4 );//set image to point to testbuffer
	/***********************************************************/

	std::string testSpace = "/panfs/panasas01/phys/phrfp/SensorAnalysisToolKit/testing/data/testWrite.raw";
	std::shared_ptr<stk::IO<unsigned short> > myImageIO(new stk::IO<unsigned short>);
	myImageIO->WriteImage( myImage, testSpace );

	EXPECT_EQ( myImageIO->ImageWritten() ,true);

	std::shared_ptr<std::vector<unsigned short> > loadedImage = myImageIO->ReadImage(testSpace);

	EXPECT_EQ( myImageIO->ImageLoaded() ,true);


}





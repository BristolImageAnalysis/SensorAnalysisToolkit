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
#include "stkImageHistogram.h"
#include "TH1.h"
/**
 * Unit tests to ensure that the image reader is working correctly for an image of 4096x4096 with 16bit pixels
 */

/**
 * First test ensures that if a correct image file is supplied then the image size is correct tested against the bytes loaded in by
 * the reader. Then that the first pixel is 25. The final check is that the
 * IO class has correcectly set the imageloaded input to true.
 */
TEST( ImageHist, InitConstructor ){

	stk::ImageHistogram<TH1F, unsigned short> myImageHistogram;
	myImageHistogram.SetTitle("Test");

	myImageHistogram.SetYAxisTitle("TestY");
	myImageHistogram.SetYAxisLog(true);

	myImageHistogram.SetXAxisTitle( "TestX" );
	myImageHistogram.SetNumberOfXBins( 100 );
	myImageHistogram.SetXLimits( -0.5, 99.5 );

	myImageHistogram.SetGridY(true);
	myImageHistogram.SetGridX(true);

	myImageHistogram.SetOutputFileNameAndPath("");
	myImageHistogram.SetOutputFileType( stk::FileType::JPG );
	std::cout << myImageHistogram << std::endl;

	EXPECT_EQ(  myImageHistogram.HistorgramTitle(), "Test" );

}

TEST( ImageHist, GenerateHistogramJPG ){

	stk::ImageHistogram<TH1F, unsigned short> myImageHistogram;
	myImageHistogram.SetTitle("Test");

	myImageHistogram.SetYAxisTitle("TestY");
	myImageHistogram.SetYAxisLog(true);

	myImageHistogram.SetXAxisTitle( "TestX" );
	myImageHistogram.SetNumberOfXBins( 16 );
	myImageHistogram.SetXLimits( -0.5, 15.5 );

	myImageHistogram.SetGridY(true);
	myImageHistogram.SetGridX(true);

	myImageHistogram.SetOutputFileNameAndPath("/panfs/panasas01/phys/phrfp/SensorAnalysisToolKit/testing/data/testHist");
	myImageHistogram.SetOutputFileType( stk::FileType::JPG );

	std::shared_ptr< stk::Image<unsigned short> > myImage( new stk::Image<unsigned short> );
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>(16,0) );

	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->at(iBuffer) = testValue;
		testValue++;

	}//Create test vector
	myImage->Initialise( testbuffer, 4, 4 );
	EXPECT_EQ( myImage->ImageSize(), 16 );
	myImageHistogram.GenerateHistogram( myImage );
	myImageHistogram.SaveHistogram();


}

TEST( ImageHist, GenerateHistogramPNG ){

	stk::ImageHistogram<TH1F, unsigned short> myImageHistogram;
	myImageHistogram.SetTitle("Test");

	myImageHistogram.SetYAxisTitle("TestY");
	myImageHistogram.SetYAxisLog(true);

	myImageHistogram.SetXAxisTitle( "TestX" );
	myImageHistogram.SetNumberOfXBins( 16 );
	myImageHistogram.SetXLimits( -0.5, 15.5 );

	myImageHistogram.SetGridY(true);
	myImageHistogram.SetGridX(true);

	myImageHistogram.SetOutputFileNameAndPath("/panfs/panasas01/phys/phrfp/SensorAnalysisToolKit/testing/data/testHist");
	myImageHistogram.SetOutputFileType( stk::FileType::PNG );

	std::shared_ptr< stk::Image<unsigned short> > myImage( new stk::Image<unsigned short> );
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>(16,0) );

	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->at(iBuffer) = testValue;
		testValue++;

	}//Create test vector
	myImage->Initialise( testbuffer, 4, 4 );
	EXPECT_EQ( myImage->ImageSize(), 16 );
	myImageHistogram.GenerateHistogram( myImage );
	myImageHistogram.SaveHistogram();


}

TEST( ImageHist, GenerateHistogram2DPNG ){

	stk::ImageHistogram<TH2F, unsigned short> myImageHistogram;
	myImageHistogram.SetTitle("Test");

	myImageHistogram.SetYAxisTitle("Row");
	myImageHistogram.SetYAxisLog(false);
	myImageHistogram.SetNumberOfYBins( 4 );
	myImageHistogram.SetYLimits( -0.5, 3.5 );

	myImageHistogram.SetXAxisTitle( "Col" );
	myImageHistogram.SetNumberOfXBins( 4 );
	myImageHistogram.SetXLimits( -0.5, 3.5 );

	myImageHistogram.SetGridY(false);
	myImageHistogram.SetGridX(false);

	myImageHistogram.SetStatBoxOptions(0);

	myImageHistogram.SetOutputFileNameAndPath("/panfs/panasas01/phys/phrfp/SensorAnalysisToolKit/testing/data/test2DHist");
	myImageHistogram.SetOutputFileType( stk::FileType::PNG );

	std::shared_ptr< stk::Image<unsigned short> > myImage( new stk::Image<unsigned short> );
	std::shared_ptr< std::vector<unsigned short> > testbuffer(new std::vector<unsigned short>(16,0) );

	unsigned short testValue =1;
	for( int iBuffer = 0; iBuffer < 16; iBuffer++ ){

		testbuffer->at(iBuffer) = testValue;
		testValue++;

	}//Create test vector
	myImage->Initialise( testbuffer, 4, 4 );
	EXPECT_EQ( myImage->ImageSize(), 16 );
	myImageHistogram.Generate2DHistogram( myImage );
	myImageHistogram.SaveHistogram();


}

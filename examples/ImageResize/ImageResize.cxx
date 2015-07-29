/*
 * ImageResize.cxx
 *
 *  Created on: 21 Jul 2015
 *      Author: lewish
 */




#include <iostream>
#include <sstream>


#include <chrono>
#include <ctime>
#include <ratio>

#include "stkImageHistogram.h"//write to histogram
#include "stkRawImageIO.h"//write pedestal in the frames
#include "stkRawImageStackIO.h"//load in the frames
#include "stkImageStack.h"//hold the files to be loaded
#include "stkImage.h"//will hold the result
#include "stkImageSum.h"//used to sum the stack
#include "stkImageDivision.h"//used to divide through to get final result
#include "stkImageVariance.h"//used for variance
#include "stkImageMask.h"
#include "stkImageBadPixelAverage.h"
#include "stkImageMinus.h"
#include "stkImageResize.h"



int main(int argc, const char** argv){

	if(argc != 8 ){
			std::cout<<"Usage: BadPixelRemoval [FILEPATH] [FILENAMEANDFORMAT] [OUTPUTFILENAMEANDPATH] [STARTINGFRAME] [NUMBEROFFILES] [ROWS] [COLS]"<<std::endl;
			std::cout<<"Only 16 bit is supported in this example"<<std::endl;
			return 0;
		}

	//Variables to hold the input parameters

	std::string  filePath, fileNameAndFormat, outFileNameAndPath;
	int startingframe, numOfFrames, rows, cols, framesize;
	//
	std::stringstream inputs;
	for(int iArg=1; iArg < argc; iArg++){
			inputs << argv[iArg] << ' ';//get the arguments
			}

	inputs >> filePath >> fileNameAndFormat >> outFileNameAndPath >> startingframe >> numOfFrames  >> rows >> cols;//write the parameters into setup
	framesize = cols*rows;




	//Load Image Stack
	stk::IOImageStack<unsigned short> myIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > myImageStack( new stk::ImageStack<unsigned short> );
	myImageStack->Initialise( myIO.ReadImageStack( filePath, fileNameAndFormat, startingframe, numOfFrames, framesize ), numOfFrames, rows, cols );


	//Sum
	stk::ImageSum<unsigned short> mySummer;
	//divide
	stk::ImageDivision<unsigned short> myDivider;
	stk::ImageResize<unsigned short> mySize;

	//Image to hold pedestal
	std::shared_ptr< stk::Image<unsigned short> > myPedestal ( new stk::Image<unsigned short>(4096,4096) );
	//Image to hold variance
	std::shared_ptr<stk::Image<unsigned short> > myVarianceImage ( new stk::Image<unsigned short>(1024,1024) );



	std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();//used to find the time it takes for Image to run

	mySummer.SumImageStack( myImageStack, myPedestal );

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();//some timing info

	myDivider.DivideImage(myPedestal, static_cast<unsigned short>(myImageStack->NumberOfImageInStack()) );
	std::cout<<"Ped done"<<std::endl;
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	mySize.ResizeImage(myPedestal, myVarianceImage);

	std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();



	std::chrono::steady_clock::time_point t4 = std::chrono::steady_clock::now();









	//set up hist
			stk::ImageHistogram<TH2F, unsigned short> myImageHistogram;
			myImageHistogram.SetTitle("resize");

			myImageHistogram.SetYAxisTitle("Row");
			myImageHistogram.SetYAxisLog(false);
			myImageHistogram.SetNumberOfYBins( 1024 );
			myImageHistogram.SetYLimits( -0.5, 1023.5 );

			myImageHistogram.SetXAxisTitle( "Col" );
			myImageHistogram.SetNumberOfXBins( 1024 );
			myImageHistogram.SetXLimits( -0.5, 1023.5  );

			myImageHistogram.SetGridY(false);
			myImageHistogram.SetGridX(false);

			myImageHistogram.SetStatBoxOptions(0);

			myImageHistogram.SetOutputFileNameAndPath(outFileNameAndPath);
			myImageHistogram.SetOutputFileType( stk::FileType::PNG );

			myImageHistogram.Generate2DHistogram( myVarianceImage );
			myImageHistogram.SaveHistogram();





		std::chrono::duration<double> time_span_1 = std::chrono::duration_cast<std::chrono::duration<double> >(t1 - t0);
		std::chrono::duration<double> time_span_2 = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
		std::chrono::duration<double> time_span_3 = std::chrono::duration_cast<std::chrono::duration<double> >(t3 - t2);
		std::chrono::duration<double> time_span_4 = std::chrono::duration_cast<std::chrono::duration<double> >(t4 - t3);


		std::cout << "Time for Image Sum " << time_span_1.count() << " seconds." << std::endl;
		std::cout << "Time for Image Division " << time_span_2.count() << " seconds." << std::endl;
		std::cout << "Time for Variance " << time_span_3.count() << " seconds." << std::endl;
		std::cout << "Time for Mask Generation " << time_span_4.count() << " seconds." << std::endl;
		//std::cout << "Time for Bad Pixel averaging " << time_span_5.count() << " seconds." << std::endl;
		return 1;
}

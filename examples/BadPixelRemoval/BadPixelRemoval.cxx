/*
 * BadPixelRemoval.cxx
 *
 *  Created on: 20 Jul 2015
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

	if(argc != 10 ){
			std::cout<<"Usage: BadPixelRemoval [PEDFILEPATH] [PEDFILENAMEANDFORMAT] [OUTPUTFILENAMEANDPATH]  [FILEPATH] [FILENAMEANDFORMAT] [ROWS] [COLS] [STARTINGFRAME] [NUMBEROFFILES]"<<std::endl;
			std::cout<<"Only 16 bit is supported in this example"<<std::endl;
			return 0;
		}

	//Variables to hold the input parameters

	std::string pedfilePath, pedfileNameAndFormat, filePath, fileNameAndFormat, outFileNameAndPath;
	int startingframe, numOfFrames, rows, cols, framesize;
	//
	std::stringstream inputs;
	for(int iArg=1; iArg < argc; iArg++){
			inputs << argv[iArg] << ' ';//get the arguments
			}

	inputs >> pedfilePath >> pedfileNameAndFormat >> outFileNameAndPath >> filePath >> fileNameAndFormat >> rows >> cols >> startingframe >> numOfFrames ;//write the parameters into setup
	framesize = cols*rows;


	//Load ped image stack
	stk::IOImageStack<unsigned short> mypedIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > myPedImageStack( new stk::ImageStack<unsigned short> );
	myPedImageStack->Initialise( mypedIO.ReadImageStack( pedfilePath, pedfileNameAndFormat, startingframe, numOfFrames, framesize ), numOfFrames, rows, cols );

	//Load Image Stack
	stk::IOImageStack<unsigned short> myIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > myImageStack( new stk::ImageStack<unsigned short> );
	myImageStack->Initialise( myIO.ReadImageStack( filePath, fileNameAndFormat, startingframe, numOfFrames, framesize ), numOfFrames, rows, cols );






	/*
	 * Declaring things
	 *
	 */

	//Sum
	stk::ImageSum mySummer;

	//divide
	stk::ImageDivision myDivider;

	//variance
	stk::ImageVariance myVarianceCalc;

	//mask
	stk::ImageMask myMask;

	//Pixel average
	stk::ImageBadPixelAverage myAverage;

	//Ped Remover
	stk::ImageMinus myMinus;

	//resizer
	stk::ImageResize mySize;



	/*
	 * Image initialising
	 *
	 *
	 */

	//Image to hold pedestal
	std::shared_ptr< stk::Image<float> > myPedestal ( new stk::Image<float>(4096,4096) );

	//Image to hold variance
	std::shared_ptr<stk::Image<float> > myVarianceImage ( new stk::Image<float>(4096,4096) );

	//Image to hold mask
	std::shared_ptr<stk::Image<bool> > myMaskImage ( new stk::Image<bool>(4096,4096) );

	//Image to hold result
	std::shared_ptr<stk::Image<float> > myResult (new stk::Image<float>(4096,4096));

	//Image to hold resized result
	std::shared_ptr<stk::Image<float> > myResultResize (new stk::Image<float>(1024,1024));





	/*
	 * Begin arithmetic
	 *
	 */

	std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();//used to find the time it takes for Image to run


	//summing ped stack
	mySummer.SumImageStack( myPedImageStack, myPedestal );

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();//some timing info

	//dividing the image stack
	myDivider.DivideImage(myPedestal, static_cast<float>(myPedImageStack->NumberOfImageInStack()) );


	std::cout<<"Ped done"<<std::endl;
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	//Variance Calculation
	myVarianceCalc.VarianceImageStack(myPedImageStack, myPedestal, myVarianceImage);//calculate vairance
	std::cout<<"Variance done"<<std::endl;
	std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();


	//Create mask image
	myMask.MaskImage(myVarianceImage, myMaskImage, myPedestal, 400, 50, 3200, 100);
	std::cout<<"Mask done"<<std::endl;

//	stk::IO<unsigned short> imageIO;
//	imageIO.WriteImage( myVarianceImage, outFileNameAndPath );

	//remove ped from image stack
	myMinus.MinusImage(myImageStack, myPedestal);
	std::chrono::steady_clock::time_point t4 = std::chrono::steady_clock::now();


	//Averaging the bad pixels
	myAverage.BadPixelAverage(myImageStack, myMaskImage);
	std::chrono::steady_clock::time_point t5 = std::chrono::steady_clock::now();



	//sum the stack
	mySummer.SumImageStack(myImageStack, myResult);
	myDivider.DivideImage(myResult, static_cast<float>(myImageStack->NumberOfImageInStack()) );//divide by number in stack
	std::cout<<"Image done done"<<std::endl;

	//Resizing Image
	mySize.ResizeImage(myResult, myResultResize);





	//set up hist
			stk::ImageHistogram<TH2F, float> myImageHistogram;
			myImageHistogram.SetTitle("ds");

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

			myImageHistogram.Generate2DHistogram( myResultResize );
			myImageHistogram.SaveHistogram();





		std::chrono::duration<double> time_span_1 = std::chrono::duration_cast<std::chrono::duration<double> >(t1 - t0);
		std::chrono::duration<double> time_span_2 = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
		std::chrono::duration<double> time_span_3 = std::chrono::duration_cast<std::chrono::duration<double> >(t3 - t2);
		std::chrono::duration<double> time_span_4 = std::chrono::duration_cast<std::chrono::duration<double> >(t4 - t3);
		std::chrono::duration<double> time_span_5 = std::chrono::duration_cast<std::chrono::duration<double> >(t5 - t4);

		std::cout << "Time for Image Sum " << time_span_1.count() << " seconds." << std::endl;
		std::cout << "Time for Image Division " << time_span_2.count() << " seconds." << std::endl;
		std::cout << "Time for Variance " << time_span_3.count() << " seconds." << std::endl;
		std::cout << "Time for Mask Generation " << time_span_4.count() << " seconds." << std::endl;
		std::cout << "Time for Bad Pixel averaging " << time_span_5.count() << " seconds." << std::endl;
		return 1;
}

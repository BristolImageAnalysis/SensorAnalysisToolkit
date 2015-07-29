/*
 * FlatFieldCorrection.cxx
 *
 *  Created on: 22 Jul 2015
 *      Author: lewish
 */



#include <iostream>
#include <sstream>


#include <chrono>
#include <ctime>
#include <ratio>
#include <cmath>
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
#include "stkImageFlatFieldCorrection.h"


int main(int argc, const char** argv){

	if(argc != 16 ){
			std::cout<<"Usage: BadPixelRemoval [PEDFILEPATH] [PEDFILENAMEANDFORMAT] [OUTPUTFILENAMEANDPATH]  [LIGHTFILEPATH] [LIGHTFILENAMEANDFORMAT] [FILEPATH] [FILENAMEANDFORMAT] [ROWS] [COLS] [STARTINGFRAME] [NUMBEROFFILES]"<<std::endl;
			std::cout<<"Only 16 bit is supported in this example"<<std::endl;
			return 0;
		}

	//Variables to hold the input parameters

	std::string pedfilePath, pedfileNameAndFormat, lightfilePath, lightfileNameAndFormat, filePath, fileNameAndFormat, outFileNameAndPath;
	int startingframe, numOfFrames, rows, cols, framesize, pedstartingframe, pednumOfFrames, lightstartingframe, lightnumOfFrames;
	//
	std::stringstream inputs;
	for(int iArg=1; iArg < argc; iArg++){
			inputs << argv[iArg] << ' ';//get the arguments
			}

	inputs >> pedfilePath >> pedfileNameAndFormat >> outFileNameAndPath >> lightfilePath >> lightfileNameAndFormat >> filePath >> fileNameAndFormat >> rows >> cols >> startingframe >> numOfFrames >> pedstartingframe >> pednumOfFrames >> lightstartingframe >> lightnumOfFrames ;//write the parameters into setup
	framesize = cols*rows;



	std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();//used to find the time it takes for Image to run


	//Load ped image stack
	stk::IOImageStack<unsigned short> mypedIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > myPedImageStack( new stk::ImageStack<unsigned short> );
	myPedImageStack->Initialise( mypedIO.ReadImageStack( pedfilePath, pedfileNameAndFormat, pedstartingframe, pednumOfFrames, framesize ), pednumOfFrames, rows, cols );

	//Load light image stack
	stk::IOImageStack<unsigned short> mylightIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > mylightStack( new stk::ImageStack<unsigned short> );
	mylightStack->Initialise( mylightIO.ReadImageStack( lightfilePath, lightfileNameAndFormat, lightstartingframe, lightnumOfFrames, framesize ), lightnumOfFrames, rows, cols );

	//Load Image Stack
	stk::IOImageStack<unsigned short> myIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > myImageStack( new stk::ImageStack<unsigned short> );
	myImageStack->Initialise( myIO.ReadImageStack( filePath, fileNameAndFormat, startingframe, numOfFrames, framesize ), numOfFrames, rows, cols );

	std::cout<<"Images Loaded."<<std::endl;
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();//some timing info



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

	//FieldCorrecter
	stk::ImageFlatFieldCorrection myField;



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

	//Image to hold gain
	std::shared_ptr<stk::Image<float> > myGain (new stk::Image<float>(4096,4096));

	//Image to hold resized result
	std::shared_ptr<stk::Image<float> > myResultResize (new stk::Image<float>(1024,1024));


	std::shared_ptr<stk::Image<float> > myNumMask(new stk::Image<float>(4096,4096));


	/*
	 * Begin arithmetic
	 *
	 */

	//summing ped stack
	mySummer.SumImageStack( myPedImageStack, myPedestal );


	//dividing the image stack
	myDivider.DivideImage(myPedestal, static_cast<float>(myPedImageStack->NumberOfImageInStack()) );

	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();






	//Variance Calculation
	myVarianceCalc.VarianceImageStack(myPedImageStack, myPedestal, myVarianceImage);//calculate vairance
	std::cout<<"Variance done"<<std::endl;
	std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();






	//remove ped from image stack
	myMinus.MinusImage(myImageStack, myPedestal, myResult);

	//sum the stack

	myDivider.DivideImage(myResult, static_cast<float>(myImageStack->NumberOfImageInStack()) );
	std::chrono::steady_clock::time_point t4 = std::chrono::steady_clock::now();
//
//	for(int iFrames=0; iFrames<myPedImageStack->NumberOfImageInStack(); iFrames++)
//
//	for(int iElements=0; iElements<myVarianceImage->NumberOfPixels();iElements++){
//				float temp = (myPedImageStack->GetPixelAt(iFrames*myPedestal->NumberOfPixels()+iElements)-myPedestal->GetPixelAt(iElements));
//				float pix = myNumMask->GetPixelAt(iElements);
//				pix = pix + temp;
//				myNumMask->SetPixelAt(iElements,pix);
//			}
//	myDivider.DivideImage(myNumMask, static_cast<float>(myPedImageStack->NumberOfImageInStack()));

	//Flat field correction
	myField.CorrectImage(mylightStack, myPedestal, myResult, myGain);
	std::chrono::steady_clock::time_point t5 = std::chrono::steady_clock::now();




	//Create mask image
	myMask.MaskImage(myResult, myVarianceImage, myMaskImage , myPedestal,myGain, 400, 10, 3200, 500);
	std::cout<<"Mask done"<<std::endl;

	std::chrono::steady_clock::time_point t6 = std::chrono::steady_clock::now();



	//Averaging the bad pixels
	myAverage.BadPixelAverage(myResult, myMaskImage);
	std::chrono::steady_clock::time_point t7 = std::chrono::steady_clock::now();





	//divide by number in stack
	std::cout<<"Pixel Averaging Done."<<std::endl;

	std::cout<<mylightStack->NumberOfImageInStack()<<std::endl;




	//Resizing Image
	mySize.ResizeImage(myResult , myResultResize);

	stk::IO<float> imageIO;
	imageIO.WriteImage( myVarianceImage, outFileNameAndPath );

	std::chrono::steady_clock::time_point t8 = std::chrono::steady_clock::now();



	//set up hist
			stk::ImageHistogram<TH1F, float> myImageHistogram;
			myImageHistogram.SetTitle("test");

			myImageHistogram.SetYAxisTitle("Row");
			myImageHistogram.SetYAxisLog(false);
			myImageHistogram.SetNumberOfYBins(1024);
			myImageHistogram.SetYLimits( -0.5, 1023.5 );

			myImageHistogram.SetXAxisTitle( "Col" );
			myImageHistogram.SetNumberOfXBins( 5000);
			myImageHistogram.SetXLimits(  -0.5, 4999.5  );

			myImageHistogram.SetGridY(false);
			myImageHistogram.SetGridX(false);

			myImageHistogram.SetStatBoxOptions(111111);

			myImageHistogram.SetOutputFileNameAndPath(outFileNameAndPath);
			myImageHistogram.SetOutputFileType( stk::FileType::PNG );

			myImageHistogram.GenerateHistogram( myResult);
			myImageHistogram.SaveHistogram();

			std::chrono::steady_clock::time_point t9 = std::chrono::steady_clock::now();



		std::chrono::duration<double> time_span_1 = std::chrono::duration_cast<std::chrono::duration<double> >(t1 - t0);
		std::chrono::duration<double> time_span_2 = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
		std::chrono::duration<double> time_span_3 = std::chrono::duration_cast<std::chrono::duration<double> >(t3 - t2);
		std::chrono::duration<double> time_span_4 = std::chrono::duration_cast<std::chrono::duration<double> >(t4 - t3);
		std::chrono::duration<double> time_span_5 = std::chrono::duration_cast<std::chrono::duration<double> >(t5 - t4);
		std::chrono::duration<double> time_span_6 = std::chrono::duration_cast<std::chrono::duration<double> >(t6 - t5);
		std::chrono::duration<double> time_span_7 = std::chrono::duration_cast<std::chrono::duration<double> >(t7 - t6);
		std::chrono::duration<double> time_span_8 = std::chrono::duration_cast<std::chrono::duration<double> >(t8 - t7);
		std::chrono::duration<double> time_span_9 = std::chrono::duration_cast<std::chrono::duration<double> >(t9 - t8);


		std::cout << "Time for Image Loading " << time_span_1.count() << " seconds." << std::endl;
		std::cout << "Time for Ped Calculation " << time_span_2.count() << " seconds." << std::endl;
		std::cout << "Time for Variance " << time_span_3.count() << " seconds." << std::endl;
		std::cout << "Time for Image Integration " << time_span_4.count() << " seconds." << std::endl;
		std::cout << "Time for Flat Field Correction " << time_span_5.count() << " seconds." << std::endl;
		std::cout << "Time for Mask Generation " << time_span_6.count() << " seconds." << std::endl;
		std::cout << "Time for Bad Pixel Average " << time_span_7.count() << " seconds." << std::endl;
		std::cout << "Time for Image Resizing " << time_span_8.count() << " seconds." << std::endl;
		std::cout << "Time for Histogram Generation " << time_span_9.count() << " seconds." << std::endl;
		return 1;
}


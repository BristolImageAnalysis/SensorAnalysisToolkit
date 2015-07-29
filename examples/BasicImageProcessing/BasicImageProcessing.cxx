/*
 * BasicImageProcessing.cxx
 *
 *  Created on: 28 Jul 2015
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



	if(argc != 16 )
	{
			std::cout<<"Usage: BadPixelRemoval [PEDFILEPATH] [PEDFILENAMEANDFORMAT] [LIGHTFILEPATH] [LIGHTFILENAMEANDFORMAT] [RAWFILEPATH] [RAWFILENAMEANDFORMAT] [OUTPUTFILENAMEANDPATH]  [ROWS] [COLS] [PEDSTARTINGFRAME] [PEDNUMBEROFFILES] [LIGHTSTARTINGFRAME] [LIGHTNUMBEROFFILES] [RAWSTARTINGFRAME] [RAWNUMBEROFFILES]"<<std::endl;
			std::cout<<"Only 16 bit is supported in this example"<<std::endl;
			return 0;
	}



	//Variables to hold the input parameters

	std::string pedfilePath, pedfileNameAndFormat, lightfilePath, lightfileNameAndFormat, filePath, fileNameAndFormat, outFileNameAndPath;
	int startingframe, numOfFrames, rows, cols, framesize, pedStartingframe, pedNumOfFrames, lightStartingframe, lightNumOfFrames;


	std::stringstream inputs;
	for(int iArg=1; iArg < argc; iArg++)
	{
			inputs << argv[iArg] << ' ';//get the arguments
	}

	inputs >> pedfilePath >> pedfileNameAndFormat  >> lightfilePath >> lightfileNameAndFormat >> filePath >> fileNameAndFormat >> outFileNameAndPath >> rows >> cols >> pedStartingframe >> pedNumOfFrames >> lightStartingframe >> lightNumOfFrames >> startingframe >> numOfFrames ;//write the inputs
	framesize = cols*rows;


	//Load ped image stack
	stk::IOImageStack<unsigned short> mypedIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > myPedImageStack( new stk::ImageStack<unsigned short> );
	myPedImageStack->Initialise( mypedIO.ReadImageStack( pedfilePath, pedfileNameAndFormat, pedStartingframe, pedNumOfFrames, framesize ), pedNumOfFrames, rows, cols );

	//Load light image stack
	stk::IOImageStack<unsigned short> mylightIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > mylightStack( new stk::ImageStack<unsigned short> );
	mylightStack->Initialise( mylightIO.ReadImageStack( lightfilePath, lightfileNameAndFormat, lightStartingframe, lightNumOfFrames, framesize ), lightNumOfFrames, rows, cols );

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

		//FieldCorrecter
		stk::ImageFlatFieldCorrection myField;


		/*
		 * Image initialising
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



		/*
		* Begin arithmetic
		*/

		//Creating pedestal image.
		mySummer.SumImageStack( myPedImageStack, myPedestal );
		myDivider.DivideImage(myPedestal, static_cast<float>(myPedImageStack->NumberOfImageInStack()) );


		//Calculating the number of dark frames in front of the data.
		float pedAvg;
		float darkFrames=0;
		while(darkFrames==0){
		for (int iElements = 0; iElements<framesize; iElements++)
		{

			pedAvg += myPedestal->GetPixelAt(iElements);
		}
		pedAvg=pedAvg/framesize;


		for(int iFrames=0; iFrames<myImageStack->NumberOfImageInStack(); iFrames++)
		{
			float tempPix;
			for(int iElements=0; iElements<framesize;iElements++)
			{

				tempPix+=myImageStack->GetPixelAt(iElements);
			}
			tempPix=tempPix/framesize;
			if	(tempPix>pedAvg)
				{
					darkFrames=iFrames;
				}
		}
		}


		//Variance calculation
		myVarianceCalc.VarianceImageStack(myPedImageStack, myPedestal, myVarianceImage);

		//Remove pedestal from raw stack, sum stack into image.
		myMinus.MinusImage(myImageStack, myPedestal, myResult);
		myDivider.DivideImage(myResult, static_cast<float>(myImageStack->NumberOfImageInStack()) );

		//Flat field correction
		myField.CorrectImage(mylightStack, myPedestal, myResult, myGain);

		//Mask generation
		myMask.MaskImage(myResult, myVarianceImage, myMaskImage , myPedestal,myGain, 400, 10, 3200, 500);

		//Averaging the bad pixels
		myAverage.BadPixelAverage(myResult, myMaskImage);

		//Image resizing
		mySize.ResizeImage(myResult , myResultResize);



		stk::ImageHistogram<TH2F, float> myImageHistogram;
		myImageHistogram.SetTitle(outFileNameAndPath);
		myImageHistogram.SetYAxisTitle("Row");
		myImageHistogram.SetYAxisLog(false);
		myImageHistogram.SetNumberOfYBins(1024);
		myImageHistogram.SetYLimits( -0.5, 1023.5 );
		myImageHistogram.SetXAxisTitle( "Col" );
		myImageHistogram.SetNumberOfXBins( 1024);
		myImageHistogram.SetXLimits(  -0.5, 1023.5  );

		myImageHistogram.SetGridY(false);
		myImageHistogram.SetGridX(false);

		myImageHistogram.SetStatBoxOptions(111111);
		myImageHistogram.SetOutputFileNameAndPath(outFileNameAndPath);
		myImageHistogram.SetOutputFileType( stk::FileType::PNG );

		myImageHistogram.Generate2DHistogram( myResultResize);
		myImageHistogram.SaveHistogram();


	return 1;
}

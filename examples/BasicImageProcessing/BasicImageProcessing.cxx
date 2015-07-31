/*
 * BasicImageProcessing.cxx
 *
 *  Created on: 28 Jul 2015
 *      Author: lewish
 */


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

	inputs >> pedfilePath >> pedfileNameAndFormat  >> lightfilePath >> lightfileNameAndFormat >> filePath >> fileNameAndFormat >> outFileNameAndPath >> rows >> cols >> pedStartingframe >> pedNumOfFrames >> lightStartingframe >> lightNumOfFrames >> startingframe >> numOfFrames;//write the inputs
	framesize = cols*rows;

	std::cout<<"Input Works"<<std::endl;
	//Load ped image stack
	stk::IOImageStack<unsigned short> mypedIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > myPedImageStack( new stk::ImageStack<unsigned short> );
	myPedImageStack->Initialise( mypedIO.ReadImageStack( pedfilePath, pedfileNameAndFormat, pedStartingframe, pedNumOfFrames, framesize ), pedNumOfFrames, rows, cols );
	std::cout<<"ped Works"<<std::endl;
	//Load light image stack
	stk::IOImageStack<unsigned short> mylightIO;
	std::shared_ptr< stk::ImageStack<unsigned short> > mylightStack( new stk::ImageStack<unsigned short> );
	mylightStack->Initialise( mylightIO.ReadImageStack( lightfilePath, lightfileNameAndFormat, lightStartingframe, lightNumOfFrames, framesize ), lightNumOfFrames, rows, cols );
	std::cout<<"light Works"<<std::endl;
	//Load Image Stack
	//	stk::IOImageStack<unsigned short> myIO;
	//	std::shared_ptr< stk::ImageStack<unsigned short> > myImageStack( new stk::ImageStack<unsigned short> );
	//	myImageStack->Initialise( myIO.ReadImageStack( filePath, fileNameAndFormat, startingframe, numOfFrames, framesize ), numOfFrames, rows, cols );


	std::cout<<"Images loaded."<<std::endl;



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

	std::cout<<"Pedestal Calculated."<<std::endl;
	float pedAvg(0);
	for (int iElements = 0; iElements<framesize; iElements++)
	{

		pedAvg += myPedestal->GetPixelAt(iElements);
	}
	pedAvg=pedAvg/framesize;


	float pedVar(0);
	for (int iElements=0; iElements<framesize; iElements++)
	{
		pedVar+= (myPedestal->GetPixelAt(iElements)-pedAvg)*(myPedestal->GetPixelAt(iElements)-pedAvg);
	}
	pedVar=std::sqrt(pedVar/framesize);
	int NumOfImageStacks;
	double loops, dec, newframenumber;
	newframenumber=numOfFrames;
	dec = modf(newframenumber/100, &loops);

	if( dec == 0 ){
		NumOfImageStacks = loops;
	}
	else{
		NumOfImageStacks = loops +1;
	}

	std::shared_ptr< stk::ImageStack<unsigned short> > myImageStack( new stk::ImageStack<unsigned short> );
	stk::IOImageStack<unsigned short> myIO;


	int darkFlag(0);
	for ( int iter = 0; iter<NumOfImageStacks;iter++){

		if (iter==loops)
		{



			myImageStack->Initialise( myIO.ReadImageStack( filePath, fileNameAndFormat, iter*100, (100*dec), framesize ), 100*dec	, rows, cols );
			//Calculating the number of dark frames in front of the data.

			float darkFrames=0;
			float darkFramesAfter=0;



			int iFrames=0;
			do {
				float tempPix=0;
				for(int iElements=0; iElements<framesize;iElements++)
				{
					tempPix+=myImageStack->GetPixelAt(iFrames*framesize+iElements);
				}
				tempPix=tempPix/framesize;

				if	(tempPix>(pedAvg+200))
				{

						darkFrames=iFrames;
				}

			}while(darkFrames==0&&iFrames<myImageStack->NumberOfImageInStack()&&darkFlag!=1);



			//Calculating the number of dark frames after the data.
			iFrames=darkFrames;
			do {
				float tempPix=0;
				for(int iElements=0; iElements<framesize;iElements++)
				{
					tempPix+=myImageStack->GetPixelAt(iFrames*framesize+iElements);
				}
				tempPix=tempPix/framesize;

				if	(tempPix<(pedAvg+200))
				{
					darkFramesAfter=iFrames;

				}

				iFrames++;

			}while(darkFramesAfter==0&&iFrames<myImageStack->NumberOfImageInStack());
			if(darkFramesAfter==0){
							darkFramesAfter=dec*100;
						}
			std::cout<<"Dark frames excluded."<<std::endl;
			std::cout<<darkFrames<<" "<<darkFramesAfter<<std::endl;
			//Remove pedestal from raw stack, sum stack into image.
			//
			myMinus.MinusImage(myImageStack, myPedestal, myResult, darkFrames, darkFramesAfter);
			//myDivider.DivideImage(myResult, static_cast<float>(darkFramesAfter-darkFrames) );
			//

		}
		else
		{


			//stk::IOImageStack<unsigned short> myIO;
			//std::shared_ptr< stk::ImageStack<unsigned short> > myImageStack( new stk::ImageStack<unsigned short> );
			myImageStack->Initialise( myIO.ReadImageStack( filePath, fileNameAndFormat, iter*100, (100), framesize ), 100, rows, cols );
			//Calculating the number of dark frames in front of the data.

			float darkFrames=0;
			float darkFramesAfter=0;


			int iFrames=0;
			do {
				float tempPix=0;
				for(int iElements=0; iElements<framesize;iElements++)
				{
					tempPix+=myImageStack->GetPixelAt(iFrames*framesize+iElements);
				}
				tempPix=tempPix/framesize;

				if	(tempPix>(pedAvg+200))
				{

					darkFrames=iFrames;
					darkFlag=1;
				}
				iFrames++;

			}while(darkFrames==0&&iFrames<myImageStack->NumberOfImageInStack()&&darkFlag!=1);



			//Calculating the number of dark frames after the data.
			iFrames=darkFrames;
			do {
				float tempPix=0;
				for(int iElements=0; iElements<framesize;iElements++)
				{
					tempPix+=myImageStack->GetPixelAt(iFrames*framesize+iElements);
				}
				tempPix=tempPix/framesize;

				if	(tempPix<(pedAvg+200))
				{
					darkFramesAfter=iFrames;
				}

				iFrames++;


			}while(darkFramesAfter==0&&iFrames<myImageStack->NumberOfImageInStack());
			if(darkFramesAfter==0){
				darkFramesAfter=100;
			}
			//std::cout<<darkFrames<<" "<<darkFramesAfter<<std::endl;
			//std::cout<<"Dark frames excluded."<<std::endl;
			//Remove pedestal from raw stack, sum stack into image.
			myMinus.MinusImage(myImageStack, myPedestal, myResult, darkFrames, darkFramesAfter);
			//myDivider.DivideImage(myResult, static_cast<float>(darkFramesAfter-darkFrames) );
		}

	}

//float temp=0;
//	for(int iElements = 0; iElements<myResult->NumberOfPixels();iElements++){
//		temp+= myResult->GetPixelAt(iElements);
//		//std::cout<<myResult->GetPixelAt(iElements)<<std::endl;
//	}
////std::cout<<temp<<std::endl;
	//Variance calculation

	std::cout<<"Ped of Pixel 0: "<<myPedestal->GetPixelAt(0)<<std::endl;
	std::cout<<"Var of Pixel 0: "<<myVarianceImage->GetPixelAt(0)<<std::endl;
	std::cout<<"Ped subtracted stack pixel 0: "<<myPedImageStack->GetPixelAt(0)<<std::endl;

	myVarianceCalc.VarianceImageStack(myPedImageStack, myPedestal, myVarianceImage);

	std::cout<<"Var post calc of Pixel 0: "<<myVarianceImage->GetPixelAt(0)<<std::endl;


	float varAvg(0), varVar(0);
	for (int iElements = 0; iElements<framesize; iElements++)
	{
		varAvg += myVarianceImage->GetPixelAt(iElements);
	}
	varAvg=(varAvg/(float)framesize);
	std::cout<<"Ave Var: "<<varAvg<<std::endl;

	for (int iElements=0; iElements<framesize; iElements++)
	{
		varVar+= (myVarianceImage->GetPixelAt(iElements)-varAvg)*(myVarianceImage->GetPixelAt(iElements)-varAvg);
	}
	varVar=std::sqrt(varVar/(float)framesize);

	std::cout<<"Variance calculated."<<std::endl;

	std::cout<<"Images integrated."<<std::endl;

	//Flat field correction
	myField.CorrectImage(mylightStack, myPedestal, myResult, myGain);

	std::cout<<"Cut values Ped: "<<pedAvg<<" Var: "<<varVar<<std::endl;

	//Mask generation
	myMask.MaskImage(myResult, myVarianceImage, myMaskImage , myPedestal,myGain, varAvg+3*varVar, varAvg-2*varVar, pedAvg+2*pedVar, pedAvg-2*pedVar);

	//Averaging the bad pixels
	myAverage.BadPixelAverage(myResult, myMaskImage);

	std::cout<<"Bad pixels removed."<<std::endl;
	//Image resizing
	mySize.ResizeImage(myResult , myResultResize);

	stk::IO<float> imageIO;
	imageIO.WriteImage( myResult, outFileNameAndPath );

	stk::ImageHistogram<TH2F, float> myImageHistogram;
	myImageHistogram.SetTitle(fileNameAndFormat);
	myImageHistogram.SetYAxisTitle("Row");
	myImageHistogram.SetYAxisLog(false);
	myImageHistogram.SetNumberOfYBins(1024);
	myImageHistogram.SetYLimits( -0.5, 1023.5 );
	myImageHistogram.SetXAxisTitle( "Col" );
	myImageHistogram.SetNumberOfXBins( 1024);
	myImageHistogram.SetXLimits(  -0.5, 1023.5  );

	myImageHistogram.SetGridY(false);
	myImageHistogram.SetGridX(false);

	myImageHistogram.SetStatBoxOptions(0);
	myImageHistogram.SetOutputFileNameAndPath(outFileNameAndPath);
	myImageHistogram.SetOutputFileType( stk::FileType::PNG );

	myImageHistogram.Generate2DHistogram( myResultResize);
	myImageHistogram.SaveHistogram();


	return 1;
}

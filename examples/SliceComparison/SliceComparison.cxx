/*
 * SliceComparison.cxx
 *
 *  Created on: 31 Jul 2015
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

	std::shared_ptr<stk::Image<float> > myResult (new stk::Image<float>(4096,4096));
	float a(4);
	for(int iElements=0; iElements<myResult->NumberOfPixels();iElements++){
		myResult->SetPixelAt(iElements, a);
		a++;
	}


	stk::ImageHistogram<TH2F, float> myImageHistogram;
	myImageHistogram.SetTitle("a");
	myImageHistogram.SetYAxisTitle("Row");
	myImageHistogram.SetYAxisLog(false);
	myImageHistogram.SetNumberOfYBins(4096);
	myImageHistogram.SetYLimits( -0.5, 1023.5 );
	myImageHistogram.SetXAxisTitle( "Col" );
	myImageHistogram.SetNumberOfXBins( 1024);
	myImageHistogram.SetXLimits(  -0.5, 1023.5  );

	myImageHistogram.SetGridY(false);
	myImageHistogram.SetGridX(false);

	myImageHistogram.SetStatBoxOptions(0);
	myImageHistogram.SetOutputFileNameAndPath("a");
	myImageHistogram.SetOutputFileType( stk::FileType::PNG );

	myImageHistogram.Generate2DHistogram( myResult);
	myImageHistogram.GenerateSlice();
	myImageHistogram.SaveHistogram();


}

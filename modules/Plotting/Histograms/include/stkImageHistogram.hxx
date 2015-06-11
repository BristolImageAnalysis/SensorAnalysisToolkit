/*
 * stkImageHistogram.hxx
 *
 *  Created on: 10 Jun 2015
 *      Author: phrfp
 */

#ifndef __stkImageHistogram_hxx
#define __stkImageHistogram_hxx

#include "stkImageHistogram.h"
#include "TCanvas.h"
#include "TImage.h"
#include "TH2.h"
#include "TH1.h"
#include "TStyle.h"

namespace stk{

template<class T_Hist, typename T_Pixeltype>
ImageHistogram<T_Hist, T_Pixeltype>::ImageHistogram() {

	m_HistSetup.mainTitle = "";
	m_HistSetup.ouputfileNameAndPath ="";
	m_HistSetup.histFileType = FileType::PNG;
	m_HistSetup.statOptions= 1111;
	m_HistSetup.x_axisTitle="";
	m_HistSetup.numberOfXBins=0;
	m_HistSetup.xstart=0;
	m_HistSetup.xend=0;
	m_HistSetup.gridX =false;
	m_HistSetup.numberOfYBins=0;
	m_HistSetup.ystart=0;
	m_HistSetup.yend=0;
	m_HistSetup.y_axisTitle ="";
	m_HistSetup.logY=false;
	m_HistSetup.gridY=false;

}

template<class T_Hist, typename T_Pixeltype>
ImageHistogram<T_Hist, T_Pixeltype>::~ImageHistogram(){

	m_histogram.reset();

}

template<class T_Hist, typename T_Pixeltype>
void ImageHistogram<T_Hist, T_Pixeltype>::GenerateHistogram( const std::shared_ptr< stk::Image<T_Pixeltype> > imageToHistogram ){

	m_histogram.reset( new T_Hist( m_HistSetup.mainTitle.c_str() , m_HistSetup.mainTitle.c_str(),
			m_HistSetup.numberOfXBins, m_HistSetup.xstart, m_HistSetup.xend) );

	typename std::vector<T_Pixeltype>::iterator imageIt;
	for( imageIt = imageToHistogram->StartImage(); imageIt != imageToHistogram->EndImage(); imageIt++ )
		m_histogram->Fill( (*imageIt) );

}

template< class T_Hist, typename T_Pixeltype >
void ImageHistogram<T_Hist, T_Pixeltype>::Generate2DHistogram( const std::shared_ptr< stk::Image<T_Pixeltype> >  imageToHistogram ){

	m_histogram.reset( new T_Hist( m_HistSetup.mainTitle.c_str() , m_HistSetup.mainTitle.c_str(),
			m_HistSetup.numberOfXBins, m_HistSetup.xstart, m_HistSetup.xend,
			m_HistSetup.numberOfYBins, m_HistSetup.ystart, m_HistSetup.yend) );

	for( int irows = 0; irows < imageToHistogram->NumberOfRows(); irows++ ){
		for( int icols = 0; icols < imageToHistogram->NumberOfColumns(); icols++ ){
			m_histogram->Fill( icols, irows, imageToHistogram->GetPixelAt(irows,icols) );
		}
	}

}


template<class T_Hist, typename T_Pixeltype>
void ImageHistogram<T_Hist, T_Pixeltype>::SaveHistogram(){

	std::shared_ptr<TCanvas> histCanvas( new TCanvas() );
	histCanvas->SetGridx( m_HistSetup.gridX );
	histCanvas->SetGridy( m_HistSetup.gridY );
	histCanvas->SetLogy( m_HistSetup.logY );

	histCanvas->SetTitle( m_HistSetup.mainTitle.c_str() );
	m_histogram->GetXaxis()->SetTitle( m_HistSetup.x_axisTitle.c_str() ) ;
	m_histogram->GetYaxis()->SetTitle( m_HistSetup.y_axisTitle.c_str() ) ;

	gStyle->SetOptStat( m_HistSetup.statOptions );

	m_histogram->Draw("COLZ");

	std::shared_ptr<TImage> img(TImage::Create());
	img->FromPad( histCanvas.get() );

	std::string tempName=m_HistSetup.ouputfileNameAndPath;

	switch(  m_HistSetup.histFileType()  ){
		case FileType::JPG:
			tempName += ".jpg";
			img->SetImageQuality (TAttImage::EImageQuality::kImgBest);
			img->WriteImage( tempName.c_str());
			break;
		case FileType::PNG:
			tempName += ".png";
			img->WriteImage( tempName.c_str());
			break;
		default:
			break;
	}

	histCanvas.reset();
	img.reset();

}

}

#endif /* MODULES_PLOTTING_HISTOGRAMS_INLCUDE_STKIMAGEHISTOGRAM_HXX_ */

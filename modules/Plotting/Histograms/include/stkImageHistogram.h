/*
 * stkImageHistogram.h
 *
 *  Created on: 10 Jun 2015
 *      Author: phrfp
 */



#ifndef __stkImageHistogram_h
#define __stkImageHistogram_h

#include <string>
#include <iostream>
#include <memory>

#include "stkImage.h"

namespace stk{

///
struct FileType
{
    enum Type
    {
    	JPG, PNG
    };

    FileType() : t_(PNG) {}
    FileType(Type t) : t_(t) {}
    Type operator() () const {return t_;}
    //int operator() const{return t_;}
    friend std::ostream& operator <<( std::ostream& osObject, const FileType &fileExt ){
    	return fileExt.PrintExtType(  osObject );
    }

private:
    std::ostream& PrintExtType( std::ostream& osObject ) const{
		switch(t_){
		case FileType::JPG:
			osObject << "JPEG";
			return osObject;
		case FileType::PNG:
			osObject << "PNG";
			return osObject;
		default:
			return osObject;
		}
    }
   //prevent automatic conversion for any other built-in types such as bool, int, etc
   template<typename T>
    operator T () const;
	Type t_;

};
///

template< class T_Hist, typename T_Pixeltype>
class ImageHistogram{

public:

	ImageHistogram();
	virtual ~ImageHistogram();

	inline void SetTitle(const std::string &mainTitle){ m_HistSetup.mainTitle = mainTitle; };

	inline void SetYAxisTitle(const std::string &y_axisTitle){ m_HistSetup.y_axisTitle = y_axisTitle; };
	inline void SetNumberOfYBins( const int &numberOfYBins ){ m_HistSetup.numberOfYBins = numberOfYBins; };
	inline void SetYLimits( const float &yLowerLimit, const float &yUpperLimit ){ m_HistSetup.ystart = yLowerLimit; m_HistSetup.yend = yUpperLimit; };
	inline void SetYAxisLog(const bool &logy){ m_HistSetup.logY = logy; };
	inline void SetGridY(const bool &gridY){ m_HistSetup.gridY = gridY;};

	inline void SetXAxisTitle(const std::string &x_axisTitle){ m_HistSetup.x_axisTitle = x_axisTitle; };
	inline void SetNumberOfXBins( const int &numberOfXBins ){ m_HistSetup.numberOfXBins = numberOfXBins; };
	inline void SetXLimits( const float &xLowerLimit, const float &xUpperLimit ){ m_HistSetup.xstart = xLowerLimit; m_HistSetup.xend = xUpperLimit; };
	inline void SetGridX(const bool &gridX){ m_HistSetup.gridX = gridX;};

	inline void SetStatBoxOptions( const int &statOptions ){ m_HistSetup.statOptions = statOptions; };

	inline void SetOutputFileNameAndPath( const std::string &fileNameAndPath ){ m_HistSetup.ouputfileNameAndPath = fileNameAndPath; };

	inline void SetOutputFileType( const FileType &extType ){ m_HistSetup.histFileType = extType; };

	inline const std::string &HistorgramTitle() const { return m_HistSetup.mainTitle; };

	friend std::ostream& operator <<(std::ostream& osObject, const ImageHistogram<T_Hist, T_Pixeltype>& histogram )
	{
		return histogram.m_HistSetup.PrintSettings(osObject); //just one line!
	};

	void GenerateHistogram( const std::shared_ptr< stk::Image<T_Pixeltype> >  imageToHistogram );
	void Generate2DHistogram( const std::shared_ptr< stk::Image<T_Pixeltype> >  imageToHistogram );

	void SaveHistogram();

private:

	std::shared_ptr< T_Hist > m_histogram;

	struct HistSettings{
		std::string x_axisTitle; //x axis title
		float xstart;
		float xend;
		int numberOfXBins;//number of x bins
		bool gridX;

		float ystart;
		float yend;
		int numberOfYBins;//number of x bins
		bool logY;//set y to log
		std::string y_axisTitle;//y_axis title
		bool gridY;

		std::string mainTitle;//maintitle
		int statOptions;
		std::string ouputfileNameAndPath; //output path and file name written as png
		FileType histFileType;


		std::ostream&  PrintSettings(std::ostream & out) const
		{
			out << "========Main Settings ====== "<< std::endl;
			out << "==== main title: "<<mainTitle<<std::endl;
			out << "==== output filename " << ouputfileNameAndPath <<std::endl;
			out << "==== file type "<< histFileType <<std::endl;

			out << "========x Settings ====== "<< std::endl;
		    out << "==== x axis title: " << x_axisTitle <<std::endl;
		    out << "==== x bins: " << numberOfXBins <<std::endl;
		    out << "==== x lower bound: " << xstart <<std::endl;
		    out << "==== x upper bound: " << xend <<std::endl;
		    out << "==== x griddy: " << gridX <<std::endl;

		    out << "========y Settings ====== "<< std::endl;
		    out << "==== y axis title: " << y_axisTitle <<std::endl;
		    out << "==== y log: " << logY <<std::endl;
		    out << "==== y griddy: " << gridY <<std::endl;


		    return out;
		}


	};
	HistSettings m_HistSetup;

};

}

#include "stkImageHistogram.hxx"

#endif /* __stkImageHistogram_h */

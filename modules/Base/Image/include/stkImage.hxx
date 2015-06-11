/*
 * stkImage.hxx
 *
 *  Created on: 2 Jun 2015
 *      Author: phrfp
 */

#ifndef __stkImage_hxx
#define __stkImage_hxx
#include "stkImage.h"


namespace stk{

template<typename T_PixelType>//Default constructor
Image<T_PixelType>::Image() : m_row(0), m_col(0){//init values to 0

}

template<typename T_PixelType>
Image<T_PixelType>::Image( const int &row, const int &col ) : m_row(row), m_col(col){
	m_buffer.reset( new std::vector<T_PixelType>( (m_row*m_col), 0) );//create image with element initialised to 0
}

template<typename T_PixelType>
Image<T_PixelType>::~Image(){
	m_buffer.reset();//delete managed object
}

template<typename T_PixelType>
void Image<T_PixelType>::Initialise( const std::shared_ptr< std::vector<T_PixelType> > buffer, const int &row, const int &col ){

	m_buffer = buffer; //take ownership of buffer
	m_row = row;
	m_col = col;
}

}

#endif /* __stkImage_hxx */

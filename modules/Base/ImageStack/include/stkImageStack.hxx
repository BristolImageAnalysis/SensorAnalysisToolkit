/*=======================================
 * stkImageStack.hxx
 *
 *  Created on: 8 Jun 2015
 *      Author: phrfp
 *========================================*/

#ifndef __stkImageStack_hxx
#define __stkImageStack_hxx

#include "stkImageStack.h"

namespace stk{

template <typename T_PixelType> // Initialise member variables
ImageStack<T_PixelType>::ImageStack() : m_numberOfFrames(0), m_col(0), m_row(0), m_frameSize(0){

}

template <typename T_PixelType>
ImageStack<T_PixelType>::~ImageStack(){ m_imageStack.reset(); /*release the pointer to the vector of data to be deleted when no one is pointing at it*/}

template <typename T_PixelType>
void ImageStack<T_PixelType>::Initialise(std::shared_ptr< std::vector<T_PixelType> > buffer, const int &numberOfFrames, const int &col, const int &row){
	m_numberOfFrames=numberOfFrames; //set the member variables
	m_col = col;
	m_row = row;
	m_frameSize = col*row;
	m_imageStack = buffer;
}

template <typename T_PixelType>
typename std::vector<T_PixelType>::iterator ImageStack<T_PixelType>::StartOfFrame(const int &frameNumber){
	//determine iterator pos. and return it to the user.
	return (m_imageStack->begin() + (frameNumber*m_frameSize) );
}

template <typename T_PixelType>
typename std::vector<T_PixelType>::iterator ImageStack<T_PixelType>::EndOfFrame(const int &frameNumber){
	//determine iterator pos. and return it to the user.
	if( frameNumber != m_numberOfFrames ){ return ( (m_imageStack->begin() + ( (frameNumber*m_frameSize) + (m_frameSize) ) ) );}//
	else{ return m_imageStack->end(); }
}

}

#endif /* __stkImageStack_h */

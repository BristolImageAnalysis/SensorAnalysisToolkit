/*==================================================
 * stkImageStack.h
 *
 *  Created on: 8 Jun 2015
 *      Author: phrfp
 *==================================================*/

#ifndef __stkImageStack_h
#define __stkImageStack_h

#include <memory>
#include <vector>
#include <iterator>

namespace stk{

/**
 * \class ImageStack
 * \brief Holds a collection of images that are accessed though std::vector iterators.
 *
 * Essentially a wrapper around std::vector providing methods for iterator calculations to obtain the pixel data.
 *
 */

template <typename T_PixelType>
class ImageStack{

public:
	/**
	 * Default constructor - initialises member variables to defaults
	 */
	ImageStack();
	/**
	 * Default destructor - resets the shared pointer to image stack so that memory can be deallocated
	 */
	virtual ~ImageStack();
	/**
	 * Intialises the Image stack so that image stack has ownership of the memory
	 * @par[in] buffer The buffer that has the pixel data.
	 * @par[in] numberOfFrames The number of frames loaded.
	 * @par[in] col Number of columns in the sensor.
	 * @par[in] row Number of rows in the sensor.
	 */
	void Initialise( const std::shared_ptr< std::vector<T_PixelType> > buffer, const int &numberOfFrames, const int &col, const int &row );
	/**
	 * Gives the iterator to the start of the frame for a given frame number
	 * @par[in] frameNumber The frame number that the user wants the iterator to point too.
	 * \return An iterator to the start of the image that has been requested.
	 */
	typename std::vector<T_PixelType>::iterator StartOfFrame(const int &frameNumber);

	typename std::vector<T_PixelType>::iterator EndOfFrame(const int &frameNumber);

	/**
	 * Tells the user how many frames are in the stack.
	 * \return The number of frames in the stack.
	 */
	inline int NumberOfImageInStack(){return m_numberOfFrames;};

	/**
	 * Gives the value of the pixel at that position in the image stack
	 * @par[in] position The position of the pixel in the image stack.
	 * \return A const reference to the pixel value.
	 */
	inline const T_PixelType& GetPixelAt(const int &position){return m_imageStack->at(position);};
	/*
	 * Finds the size of the stack as an int number of images.
	 */
	inline int SizeOfStack(){return m_numberOfFrames*m_frameSize;};
	/*
	 * sets pixel value in stack
	 */
	inline void SetPixelAt(const int &position, const T_PixelType &value){ m_imageStack->at(position)=value;};


private:

	int m_numberOfFrames; /*< The number of frames in the stack */
	int m_col;/*< The number of coloumns in the image */
	int m_row;/*< The number of rows in the image */
	int m_frameSize;/*< The size of the frame calc as row*col */
	std::shared_ptr< std::vector<T_PixelType> > m_imageStack; /*< A pointer to the vector holding the image stack */
};

}

#include "stkImageStack.hxx"

#endif /* __stkImageStack_h */

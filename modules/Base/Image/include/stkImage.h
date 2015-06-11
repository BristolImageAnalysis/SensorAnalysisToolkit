/*
 * stkImage.h
 *
 *  Created on: 2 Jun 2015
 *      Author: phrfp
 */

#ifndef __stkImage_h
#define __stkImage_h

#include <memory>
#include <iterator>
#include <vector>

namespace stk{
/**
 * \class Image
 * \brief Image class that allows user to construct images, access and set the pixels that are held in a std::vector container.
 *
 * Image class holds the image as a vector and has access methods set and get pixel values at a certain coordinate.
 *
 */

template<typename T_PixelType>
class Image{
public:
	/**
	 * Default constructor - initialises the member variables to default
	 */
	Image();
	/**
	 * Constructor initialises the memory for an image of a given size.
	 */
	Image( const int &row, const int &col );
	/**
	 * Destructor resets the shared pointer to the image vector so that use count is decremented.
	 */
    virtual ~Image();
    /**
     * Initialise an image to point at a vector of data that has been read into memory.
     * @par[in] buffer Shared pointer to the vector that has been loaded into memory. Must be a single image.
     * @par[in] row Number of rows in the image to be initialised.
     * @par[in] col Number of columns in the image to be initialised.
     */
    void Initialise( const std::shared_ptr< std::vector<T_PixelType> > buffer, const int &row, const int &col );

    /**
     * Gives the iterator to the start of the image.
     *\return iterator of type defined by the pixel size of the image to the start of the image
     */
    typename std::vector<T_PixelType>::iterator StartImage(){return m_buffer->begin();};//returns a pointer to the start of the image buffer

    /**
     * Gives the iterator to the end of the image.
     *\return iterator of type defined by the pixel size of the image to the end of the image
     */
    typename std::vector<T_PixelType>::iterator EndImage(){return m_buffer->end();};//returns a pointer to the start of the image buffer


    /**
     * Gives the size of the image in bytes that has been initialised
     * \return Number of bytes in the image.
     */
    const int SizeInBytes(){if(!m_buffer->empty()) return ( m_buffer->size()*sizeof(T_PixelType) ); return 0;};//the length in bytes of the buffer
    /**
     * Gives the total size of the buffer i.e the number of elements stored in the vector
     * \return Number of elements in the vector
     */
    const int ImageSize(){if(!m_buffer->empty()) return ( m_buffer->size() ); return 0;};

    /**
     * Gives the number of columns in the image.
     * \return The number of columns in the image.
     */
    inline const int &NumberOfColumns(){return m_col;};
    /**
     * Gives the number of rows in the image.
     * \return The number of rows in the image.
     */
    inline const int &NumberOfRows(){return m_row;};

    /**
     * Gives the total number of pixels in the image.
     * \return The total number of pixels in the image.
     */
    inline const int NumberOfPixels(){return (m_row*m_col);};

    /**
     * Access the value of a pixel at a given position in the image.
     * @par[in] position The position in image when the image is considered as a 1D array.
     * \return The value of the pixel at the specified position
     */
	inline const T_PixelType& GetPixelAt(const int &position){return m_buffer->at(position);};

	/**
	 * Access the value of a pixel at a given coordinate.
	 * @par[in] row The row the pixel is in.
	 * @par[in] col The column that the pixel is in.
	 * \return The value of the pixel at that coordinate.
	 */
	inline const T_PixelType& GetPixelAt(const int &row, const int &col){return m_buffer->at(m_col*row+col);};

	/**
	 * Set the value of a pixel at a given position in the image.
	 * @par[in] position The position in image when the image is considered as a 1D array.
	 * @par[in] value The value this pixel is to be set to.
	 */
	inline void SetPixelAt(const int &position, const T_PixelType &value){ m_buffer->at(position)=value;};

	/**
	 * Set the value of a pixel at a given position in the image.
	 * @par[in] row The row the pixel is in.
	 * @par[in] col The column that the pixel is in.
	 * @par[in] value The value this pixel is to be set to.
	 */
	inline void SetPixelAt(const int &row, const int &col, const T_PixelType &value){ m_buffer->at( (m_col*row+col) )=value;};

private:
   std::shared_ptr< std::vector<T_PixelType> > m_buffer;/*< A pointer to the vector containing the pixel data */
   int m_row;/*< The number of rows in the image */
   int m_col;/*< The number of columns in the image */
};

}

#include "stkImage.hxx"
#endif /* __stkImage_h */

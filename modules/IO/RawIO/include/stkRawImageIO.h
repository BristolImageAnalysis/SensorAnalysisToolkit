/*=========================================================================
 *
 *  Author Ryan Page
 *  Created on 4/6/2015
 *
 *=========================================================================*/

#ifndef __stkRawImageIO_h
#define __stkRawImageIO_h
#include <string>
#include <memory>
#include <vector>
#include "stkImage.h"


namespace stk{
/**
 * \class IO
 *  \brief Imports Raw data from a binary file with no header into into a vector of datatype of the pixel.
 *
 * Class to read and write raw pixel data into memory and out of memory. Works for single image files that contain the contents of
 * a single frame of a camera with no header information. Holds only information about the loading process.
 *
 *
 */

template<typename T_datatype>
class IO{
  
public:

	/**
	 * Default constructor - intialises the bytes loaded to 0 and loaded flag to false
	 */
    IO();
    
    /**
     * Default destructor
     */
    virtual ~IO();
    
    /**
     *	Writes a stk image to file as binary with no header. If successful the wrote flag is set to true else
     *	it will be false.
     *	@par[in] anImage A shared pointer to the image that is to be written.
     *	@par[in] filename The filename and path of where the file is to be written.
     */
    void WriteImage( std::shared_ptr<stk::Image<T_datatype> > anImage, const std::string &filename);

    /**
     * The ReadImage method takes the full name of an image to be loaded into
     * memory. This is returned as a shared pointer to a vector where the pixel data is stored.
     * If the load fails the vector returned is empty.
     * If this fails the loaded flag is set to false else if will be set to true.
     * @param[in] fullFileName Full path and file name of image.
     * \return Shared pointer to the image with the pixels data held in a vector.
     */
    std::shared_ptr< std::vector<T_datatype> > ReadImage( const std::string &fullFileName );

    /**
     * The number of bytes of the file read into the buffer. This is 0 if the attempt fails.
     */
    const int &BytesRead(){return m_sizeRead;};
    
    /**
     * Reports the status of the image loaded flag. True if last load was successful else false.
     */
     const bool &ImageLoaded(){return m_loadedFlag;};

	 /**
	 * Reports the status of the image write flag. True if last write was successful else false.
	 */
     const bool &ImageWritten(){return m_Wrote;};

private:

    bool m_loadedFlag; /**< hold the result of the last load attempt. */
    int m_sizeRead; /**< holds the number of bytes of the last image read. */
    bool m_Wrote;/**< holds the result of the last write attempt. */
    
};
}

#include "stkRawImageIO.hxx"
#endif

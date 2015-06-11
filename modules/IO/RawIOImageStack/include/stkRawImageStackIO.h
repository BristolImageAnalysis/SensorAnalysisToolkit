/*=========================================================================
 *
 *  Author Ryan Page
 *  Created on 5/6/2015
 *
 *=========================================================================*/

#ifndef __stkRamImageStackIO_h
#define __stkRamImageStackIO_h

#include <memory>
#include <vector>
#include <string>

namespace stk{

/**
 * \class IOImageStack
 * \brief IO class to read multiple 2-d RAW images into memeory
 *
 * Class designed to take a set of files and load the contents into memory. There is no account for headers or any other offset that might be the RAW file.
 *
 *
 */

template<typename T_datatype>
class IOImageStack{

public:
	/**
	 * Default constructor - initialises some of the member functions to defult values
	 */
	IOImageStack();
	/**
	 * Defualt destructor - no memory allocated in the class so default behaviour
	 */
	virtual ~IOImageStack();

	/**
	 * Read image stack loops over a set of files and loads them into memory. This is returned to user
	 * in the form of a smart pointer to a vector. In order to allocate memory correctly the user has to
	 * give the frame size i.e for 2x2 image the framesize would be 4. If the user requests a number of
	 * frames greater than the max size of the vector the number of frames to load is recalculated to take
	 * the maximum the vector can hold.
	 * @par[in] filePath Full path to the images i.e /\<home\>/\<experiment\>/
	 * @par[in] fileNameAndFormat File name including formatting characters. For instance testimage000%i.raw.
	 * @par[in] startingFrame Starting frame number.
	 * @par[in] numOfReqImages Number of images that are to be loaded.
	 * @par[in] frameSize Size of the image frame that is to be loaded into memory
	 * \return Shared pointer to a vector holding all the images in memory
	 */
	std::shared_ptr< std::vector<T_datatype> > ReadImageStack(const std::string &filePath, const std::string &fileNameAndFormat,
			const int &startingFrame, const int &numOfReqImages, const int &frameSize);

	/**
	 * Number of Frames that have been loaded. This will return the same as requested if the load is successful and if the number
	 * requested does not exceed the containers capability.
	 * \return The number of frames as an int
	 */
	inline int NumberOfLoadedFrames(){return m_loadedNumOfFrames;};
	/**
	 * The maximum buffer size in pixel elements. Calculated from member function max_size().
	 * \return The maximum number of elements the buffer can hold as an unsigned int
	 */
	inline unsigned int MaximumBufferSize(){return m_maximumBufferSize;};
	/**
	 * The number of bytes that have been loaded into memory.
	 * \return The number of bytes loaded as an int
	 */
	inline int NumberOfBytesLoaded(){return m_totalSizeOfImageRead;};
	/**
	 * Whether or not the reading of the frames was successful.
	 * \return Flag to indicate if the frames were loaded: true if yes false otherwise.
	 */
	inline bool FramesLoaded(){return m_loadedFlag;};
protected:

	/*
	 * Check that the number of requested frames will fit in the vector container.
	 * If not it will set the number so that it can fit them in the vector.
	 */
	void CheckAndAllocateMemory( std::shared_ptr< std::vector<T_datatype> > frameMemory );

private:

	bool m_loadedFlag; /*< The flag to indicate if the read function worked */
	int m_frameSize; /*< The size of the frame */
	int m_requestedNumOfFrames; /*< The number of frames as requested by the user */
	int m_loadedNumOfFrames; /*< The number of loaded frames */
	int m_totalSizeOfImageRead;/*< holds the number of bytes of the image stack. */
	unsigned int m_maximumBufferSize;/*< holds the maximum buffer size in bytes */

};


}

#include "stkRawImageStackIO.hxx"
#endif

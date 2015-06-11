/*=========================================================================
 *
 *  Author Ryan Page
 *  Created on 5/6/2015
 *
 *=========================================================================*/

#ifndef __stkRawImageStackIO_hxx
#define __stkRawImageStackIO_hxx

#include "stkRawImageStackIO.h"
#include <cmath>
#include <fstream>
#include <iterator>


namespace stk{

template <typename T_datatype>//initialise the members on constructing
IOImageStack<T_datatype>::IOImageStack() : m_loadedFlag(false), m_frameSize(0), m_requestedNumOfFrames(0), m_loadedNumOfFrames(0), m_totalSizeOfImageRead(0), m_maximumBufferSize(0)   {}

template <typename T_datatype>
IOImageStack<T_datatype>::~IOImageStack(){}

template <typename T_datatype>
std::shared_ptr< std::vector<T_datatype> > IOImageStack<T_datatype>::ReadImageStack( const std::string &filePath, const std::string &fileNameAndFormat, const int &startingFrame, const int &numOfReqImages, const int &frameSize){

	//Create the buffer to store data
	std::shared_ptr< std::vector<T_datatype> > frameMemory ( new std::vector<T_datatype> ( ) ); // memory buffer for image
	//First check that the memory being requested is ok
	m_requestedNumOfFrames = numOfReqImages; //set the member variables
	m_frameSize = frameSize;
	m_maximumBufferSize = frameMemory->max_size();
	//

	this->CheckAndAllocateMemory( frameMemory ); //check that the container has enough elements
	typename std::vector<T_datatype>::iterator bufferIterator = frameMemory->begin(); //set the iterator to the start of the buffer

	for(int iFrame=0; iFrame < m_loadedNumOfFrames; iFrame++ ){//loop over the number of frames to be loaded
		//
		if(iFrame != 0) bufferIterator = frameMemory->begin() + m_frameSize*iFrame;//move the buffer iterator after each loop
		//get file name
		char* nextFile= new char[50];
		std::sprintf( nextFile, fileNameAndFormat.c_str(), iFrame+startingFrame); //read in the new file name
		std::string fullNameAndPath = filePath + nextFile; // update the full path and file name
		//

		std::ifstream file(fullNameAndPath, std::ios::in | std::ios::binary); // Open filestream for binary reading

			if (file.is_open()){//check that the file is open
				if (!file.eof() && !file.fail()) //ensure flags error flags are not set
				{
					file.seekg(0, std::ios_base::end); // set pointer to end of file
					std::streampos fileSize = file.tellg(); //get the number of bytes in the file
					m_totalSizeOfImageRead += fileSize; // Keep a record of the number of bytes that have been read in
					file.seekg(0, std::ios_base::beg); //Set the pointer back to start of the file

					//The cast is needed to set the pixel data size
					if(iFrame==0){file.read(reinterpret_cast<char *> (&(*bufferIterator)), fileSize);} //read the data into the buffer.
					else{file.read(reinterpret_cast<char *> ( &(*bufferIterator) ), fileSize);} //Start the next frame at the end of the last
					file.close(); //close the file

				}
			}
			else{//can't open file
				std::cout<<"Cannot open File: "<<fullNameAndPath<<std::endl;//print warning
				m_loadedFlag = false; //set the loaded flag to false
				m_totalSizeOfImageRead=0; //set the number of read bytes to 0
				m_loadedNumOfFrames=0; //set number of frames loaded to 0
				return frameMemory; //return the empty frame
			}
		delete nextFile; //release memory for filename

	}
	m_loadedFlag = true; //loaded set to true
	return frameMemory; //return the frame

}

template <typename T_datatype>
void IOImageStack<T_datatype>::CheckAndAllocateMemory( std::shared_ptr< std::vector<T_datatype> > frameMemory){


	if( static_cast<unsigned int>( (m_requestedNumOfFrames*m_frameSize) ) >= m_maximumBufferSize ){ //check container is large enough
		m_loadedNumOfFrames = static_cast<int> (floor( m_maximumBufferSize/m_frameSize ));//if not recalculate the number of frames that can be handled
		frameMemory->resize(m_loadedNumOfFrames*m_frameSize);//allocate the required space in the vector

	}
	else{
		m_loadedNumOfFrames = m_requestedNumOfFrames; //set the number of frames to be read in
		frameMemory->resize( (m_loadedNumOfFrames*m_frameSize) ); //allocate the required space in the vector

	}

}

}



#endif /* __stkRawImageStackIO_hxx */

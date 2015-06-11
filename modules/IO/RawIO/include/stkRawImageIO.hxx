//
//  IO.h
//
//
//  Created by Ryan Page on 16/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __stkRawImageIO_hxx
#define __stkRawImageIO_hxx
#include <fstream>
#include <iostream>
#include <iterator>
#include "stkRawImageIO.h"
#include <algorithm>


namespace stk{

template<typename T_datatype>
IO<T_datatype>::IO() : m_loadedFlag(false), m_sizeRead(0), m_Wrote(false)  {//Initialise to defult values

}

template<typename T_datatype>
IO<T_datatype>::~IO(){

}


template<typename T_datatype>
void IO<T_datatype>::WriteImage( std::shared_ptr<stk::Image<T_datatype> > anImage, const std::string &filename ){

	std::ofstream file(filename, std::ios::out | std::ios::binary); // Open filestream for binary reading
	if (file.is_open()){//check that the file is open
		if (!file.eof() && !file.fail()) //ensure flags error flags are not set
		{
			file.write(reinterpret_cast<char *> (&(*anImage->StartImage())), sizeof(T_datatype)*anImage->ImageSize());
			file.close();
			m_Wrote=true;
			return;
		}
		file.close();
	}
	std::cout<<"Failed to write file: "<<filename<<std::endl;
	m_Wrote=false;

}


template<typename T_datatype>
std::shared_ptr< std::vector<T_datatype> > IO<T_datatype>::ReadImage( const std::string &fullFileName  ){
    

	std::shared_ptr< std::vector<T_datatype> > frameMemory ( new std::vector<T_datatype>() ); // memory buffer for image

	std::ifstream file(fullFileName, std::ios::in | std::ios::binary); // Open filestream for binary reading

		if (file.is_open()){//check that the file is open
			if (!file.eof() && !file.fail()) //ensure flags error flags are not set
			{
			    file.seekg(0, std::ios_base::end); // set pointer to end of file
			    std::streampos fileSize = file.tellg(); //get the number of bytes in the file
			    m_sizeRead = fileSize; // set the member to the size of the file
			    frameMemory->resize(fileSize); //ensure vector has allocated space
			    file.seekg(0, std::ios_base::beg); //Set the pointer back to start of the file

			    //The cast is needed to set the pixel data size
			    file.read(reinterpret_cast<char *> (&frameMemory->front()), fileSize); //read the data into the buffer.

				file.close(); //close the file
				m_loadedFlag = true; //loaded set to true
				return frameMemory; //return the frame
			}
		}

	m_loadedFlag = false; //set the loaded flag to false
	m_sizeRead=0; //set the number of read bytes to 0
	return frameMemory;
}

}

#endif


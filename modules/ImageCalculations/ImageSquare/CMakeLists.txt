#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)
#Add source headers
set(SOURCE_FILES include/stkImageSquare.hxx)
#Add headers
set(INCLUDE_FILES include/stkImageSquare.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkImageSquare SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkImageSquare PROPERTIES LINKER_LANGUAGE CXX)


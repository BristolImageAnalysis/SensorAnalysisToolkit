#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)
#Add source headers
set(SOURCE_FILES include/stkImageMask.hxx)
#Add headers
set(INCLUDE_FILES include/stkImageMask.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkImageMask SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkImageMask PROPERTIES LINKER_LANGUAGE CXX)


#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)
#Add source headers
set(SOURCE_FILES include/stkImageVariance.hxx)
#Add headers
set(INCLUDE_FILES include/stkImageVariance.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkImageVariance SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkImageVariance PROPERTIES LINKER_LANGUAGE CXX)


#CMakeList for src dir


#Add source headers
set(SOURCE_FILES include/stkImageSum.hxx)
#Add headers
set(INCLUDE_FILES include/stkImageSum.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkImageSum SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkImageSum PROPERTIES LINKER_LANGUAGE CXX)


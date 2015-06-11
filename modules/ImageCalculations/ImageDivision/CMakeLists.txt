#CMakeList for src dir


#Add source headers
set(SOURCE_FILES include/stkImageDivision.hxx)
#Add headers
set(INCLUDE_FILES include/stkImageDivision.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkImageDivision SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkImageDivision PROPERTIES LINKER_LANGUAGE CXX)


#CMakeList for src dir


#Add source headers
set(SOURCE_FILES include/stkRawImageIO.hxx)
#Add headers
set(INCLUDE_FILES include/stkRawImageIO.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkRawIO SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkRawIO PROPERTIES LINKER_LANGUAGE CXX)


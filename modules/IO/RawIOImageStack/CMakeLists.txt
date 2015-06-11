#CMakeList for src dir


#Add source headers
set(SOURCE_FILES include/stkRawImageStackIO.hxx)
#Add headers
set(INCLUDE_FILES include/stkRawImageStackIO.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkRawImageStackIO SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkRawImageStackIO PROPERTIES LINKER_LANGUAGE CXX)


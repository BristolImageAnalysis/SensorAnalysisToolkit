#CMakeList for src dir

#Add source headers
set(SOURCE_FILES include/stkImage.hxx)
#Add headers
set(INCLUDE_FILES include/stkImage.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkImage SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkImage PROPERTIES LINKER_LANGUAGE CXX)

#CMakeList for src dir


#Add source headers
set(SOURCE_FILES include/stkImageStack.hxx)
#Add headers
set(INCLUDE_FILES include/stkImageStack.h)
message( STATUS "Source files: ${SOURCE_FILES}" )
#Add library
add_library( stkImageStack SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

set_target_properties(stkImageStack PROPERTIES LINKER_LANGUAGE CXX)


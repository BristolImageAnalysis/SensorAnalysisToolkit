#CMakeList for src dir

find_package(ROOT)

#Add source headers
set(SOURCE_FILES include/stkImageHistogram.hxx)
#Add headers
set(INCLUDE_FILES include/stkImageHistogram.h )
message( STATUS "Source files: ${SOURCE_FILES}" )

set(PROJECT_RAW_IO_SOURCE $ENV{HOME}/SensorAnalysisToolKit)
set(TEST_LIB_DIR ${PROJECT_RAW_IO_SOURCE}/build/lib/)

set(EXT_PROJECTS_DIR $ENV{HOME}/Software)
set(ROOT_INCLUDE_DIRS ${EXT_PROJECTS_DIR}/root-6.0.4/include)
set(ROOT_LIB_DIR ${EXT_PROJECTS_DIR}/root-6.0.4/lib )
include_directories(${ROOT_INCLUDE_DIRS})

#Add library
add_library( stkImageHistogram SHARED ${SOURCE_FILES} ${INCLUDE_FILES} )

target_link_libraries(stkImageHistogram ${TEST_LIB_DIR}/libstkRawIO.so ${TEST_LIB_DIR}/libstkImage.so )

set_target_properties(stkImageHistogram PROPERTIES LINKER_LANGUAGE CXX)



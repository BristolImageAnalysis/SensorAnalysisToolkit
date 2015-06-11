#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR PedestalExample)
project(${PROJECT_NAME_STR})

set(CMAKE_C_COMPILER /cm/shared/languages/GCC-4.7/bin/gcc)
set(CMAKE_CXX_COMPILER /cm/shared/languages/GCC-4.7/bin/g++)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++0x)
endif()


#-------------------
# set common include folder for module
#-------------------
set(PROJECT_RAW_IO_SOURCE $ENV{HOME}/SensorAnalysisToolKit)
set(COMMON_INCLUDES ${PROJECT_RAW_IO_SOURCE}/modules/IO/RawIOImageStack/include ${PROJECT_RAW_IO_SOURCE}/modules/IO/RawIO/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/ImageStack/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/Image/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageSum/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageDivision/include)

set(STK_LIB_DIR ${PROJECT_RAW_IO_SOURCE}/build/lib)

include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cxx)
add_executable(${PROJECT_NAME_STR} ${PROJECT_SOURCE_DIR}/PedestalCalculation.cxx)
#add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(${PROJECT_NAME_STR} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${PROJECT_NAME_STR} ${STK_LIB_DIR}/libstkRawImageStackIO.so ${STK_LIB_DIR}/libstkRawIO.so ${STK_LIB_DIR}/libstkImageStack.so ${STK_LIB_DIR}/libstkImage.so ${STK_LIB_DIR}/libstkImageSum.so ${STK_LIB_DIR}/libstkImageDivision.so  )






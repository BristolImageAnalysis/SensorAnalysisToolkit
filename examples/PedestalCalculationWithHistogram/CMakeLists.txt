#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR PedestalWithHistExample)
project(${PROJECT_NAME_STR})

set(ROOT_DIR /panfs/panasas01/phys/phrfp/Software/root-6.0.4/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /panfs/panasas01/phys/phrfp/Software/root-6.0.4/cmake/modules)


find_package(ROOT REQUIRED Graf Gpad Hist RIO Tree)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++0x)
endif()


#-------------------
# set common include folder for module
#-------------------
set(PROJECT_RAW_IO_SOURCE $ENV{HOME}/SensorAnalysisToolKit)
set(COMMON_INCLUDES ${PROJECT_RAW_IO_SOURCE}/modules/IO/RawIOImageStack/include ${PROJECT_RAW_IO_SOURCE}/modules/IO/RawIO/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/ImageStack/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/Image/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageSum/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageDivision/include ${PROJECT_RAW_IO_SOURCE}/modules/Plotting/Histograms/include )

set(STK_LIB_DIR ${PROJECT_RAW_IO_SOURCE}/build/lib)

set(EXT_PROJECTS_DIR $ENV{HOME}/Software)
set(ROOT_INCLUDE_DIRS ${EXT_PROJECTS_DIR}/root-6.0.4/include)

include_directories(${COMMON_INCLUDES})
include_directories(${ROOT_INCLUDE_DIRS})

add_executable(${PROJECT_NAME_STR} ${PROJECT_SOURCE_DIR}/PedestalCalculationWithHistogram.cxx)

target_link_libraries(${PROJECT_NAME_STR} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries( ${PROJECT_NAME_STR} ${ROOT_LIBRARIES})

target_link_libraries(${PROJECT_NAME_STR} ${STK_LIB_DIR}/libstkRawImageStackIO.so ${STK_LIB_DIR}/libstkRawIO.so ${STK_LIB_DIR}/libstkImageStack.so ${STK_LIB_DIR}/libstkImage.so ${STK_LIB_DIR}/libstkImageSum.so ${STK_LIB_DIR}/libstkImageDivision.so ${STK_LIB_DIR}/libstkImageHistogram.so  )






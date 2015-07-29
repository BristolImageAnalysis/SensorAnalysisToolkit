#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)

#set(ROOT_DIR /software/root/root-6.04.00/cmake)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /software/root/root-6.04.00/cmake/modules)

set(PROJECT_NAME_STR VarianceCalculation)
project(${PROJECT_NAME_STR})

set(CMAKE_CXX_FLAGS '-std=c++11')

#find_package(ROOT REQUIRED Hist RIO Tree MathCore Gpad Gui )

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++0x)
endif()


#-------------------
# set common include folder for module
#-------------------
set(PROJECT_RAW_IO_SOURCE $ENV{HOME}/SensorAnalysisToolKit)
set(COMMON_INCLUDES ${PROJECT_RAW_IO_SOURCE}/modules/IO/RawIOImageStack/include ${PROJECT_RAW_IO_SOURCE}/modules/IO/RawIO/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/ImageStack/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/Image/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageSum/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageDivision/include ${PROJECT_RAW_IO_SOURCE}/modules/Plotting/Histograms/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageVariance/include)
set(ROOT_INCLUDE_DIRS /software/root/v6.04.00/include)

set(PROJECT_RAW_IO_LIB $ENV{HOME}/SensorAnalysisToolKit_Eclipse)
set(STK_LIB_DIR ${PROJECT_RAW_IO_LIB}/lib)


include_directories(${COMMON_INCLUDES})
include_directories(${ROOT_INCLUDE_DIRS})

add_executable(${PROJECT_NAME_STR} ${PROJECT_SOURCE_DIR}/VarianceCalculation.cxx)

target_link_libraries(${PROJECT_NAME_STR} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries( ${PROJECT_NAME_STR} /software/root/v6.04.00/lib/libHist.so /software/root/v6.04.00/lib/libCore.so /software/root/v6.04.00/lib/libRIO.so /software/root/v6.04.00/lib/libTree.so /software/root/v6.04.00/lib/libGpad.so /software/root/v6.04.00/lib/libGraf.so )
message(STATUS '${ROOT_LIBRARIES}')

target_link_libraries(${PROJECT_NAME_STR} ${STK_LIB_DIR}/libstkRawImageStackIO.dylib ${STK_LIB_DIR}/libstkRawIO.dylib ${STK_LIB_DIR}/libstkImageStack.dylib ${STK_LIB_DIR}/libstkImage.dylib ${STK_LIB_DIR}/libstkImageSum.dylib ${STK_LIB_DIR}/libstkImageDivision.dylib ${STK_LIB_DIR}/libstkImageHistogram.dylib  )






cmake_minimum_required (VERSION 2.8)

set(ROOT_DIR /software/root/root-6.04.00/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /software/root/root-6.04.00/cmake/modules)

project (SensorAnalysisToolKit)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules)

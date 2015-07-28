#Top level CMakeList for project

#cmake_minimum_required (VERSION 2.8)

#set(ROOT_DIR /panfs/panasas01/phys/phrfp/Software/root-6.0.4/cmake)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /panfs/panasas01/phys/phrfp/Software/root-6.0.4/cmake/modules)

#project (SensorAnalysisToolKit)

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/IO/RawIO)
add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/IO/RawIOImageStack)

add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/Base/Image)
add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/Base/ImageStack)

add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/ImageCalculations/ImageSum)
add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/ImageCalculations/ImageDivision)

add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/ImageCalculations/ImageSubtraction)
add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/ImageCalculations/ImageSquare)
add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/ImageCalculations/ImageVariance)

add_subdirectory ($ENV{HOME}/SensorAnalysisToolKit/modules/Plotting/Histograms)

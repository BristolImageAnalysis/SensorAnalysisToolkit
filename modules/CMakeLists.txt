#Top level CMakeList for project

#cmake_minimum_required (VERSION 2.8)

#project (SensorAnalysisToolKit)

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

add_subdirectory (${PROJECT_BASE_DIR}/modules/IO/RawIO)
add_subdirectory (${PROJECT_BASE_DIR}/modules/IO/RawIOImageStack)

add_subdirectory (${PROJECT_BASE_DIR}/modules/Base/Image)
add_subdirectory (${PROJECT_BASE_DIR}/modules/Base/ImageStack)

add_subdirectory (${PROJECT_BASE_DIR}/modules/ImageCalculations/ImageSum)
add_subdirectory (${PROJECT_BASE_DIR}/modules/ImageCalculations/ImageDivision)

add_subdirectory (${PROJECT_BASE_DIR}/modules/ImageCalculations/ImageSubtract)
add_subdirectory (${PROJECT_BASE_DIR}/modules/ImageCalculations/ImageSquare)
add_subdirectory (${PROJECT_BASE_DIR}/modules/ImageCalculations/ImageVariance)

add_subdirectory (${PROJECT_BASE_DIR}/modules/Plotting/Histograms)

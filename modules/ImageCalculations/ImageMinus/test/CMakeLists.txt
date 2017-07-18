#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR ImageMinus)
project(${PROJECT_NAME_STR})

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++0x)
endif()


#-------------------
# set common include folder for module
#-------------------
set(PROJECT_RAW_IO_SOURCE $ENV{HOME}/SensorAnalysisToolKit)
set(COMMON_INCLUDES ${PROJECT_RAW_IO_SOURCE}/modules/Base/ImageStack/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/Image/include ${PROJECT_RAW_IO_SOURCE}/modules/ImageCalculations/ImageMinus/include)
message(STATUS "Common includes ${COMMON_INCLUDES}")
set(EXT_PROJECTS_DIR /software)

#-------------------
# Module source
#-------------------
#set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)

#include_directories(${COMMON_INCLUDES})
#file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
#add_library(${PROJECT_LIB_NAME} ${SRC_FILES})

#add_subdirectory(${EXT_PROJECTS_DIR}/gtest-1.7.0)

#-------------------
# Test
#-------------------
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
set(GTEST_INCLUDE_DIRS ${EXT_PROJECTS_DIR}/gtest-1.7.0/include)

set(GTEST_LIBS_DIR ${EXT_PROJECTS_DIR}/gtest-1.7.0)
set(STK_LIB_DIR $ENV{HOME}/SensorAnalysisToolKit_Eclipse/lib)

include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cxx)
add_executable(${PROJECT_TEST_NAME} ${PROJECT_SOURCE_DIR}/stkImageMinusTest.cxx)
#add_dependencies(${PROJECT_TEST_NAME} googletest)



target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a)

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${PROJECT_TEST_NAME} stkImageStack stkImage stkImageMinus)

add_test(test1 ${PROJECT_TEST_NAME})

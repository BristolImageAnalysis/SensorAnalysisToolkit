#CMakeList for src dir

cmake_minimum_required(VERSION 2.8.8)

set(ROOT_DIR $ENV{ROOTSYS}/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/cmake/modules)

set(PROJECT_NAME_STR ImageHist)
project(${PROJECT_NAME_STR})

find_package(Threads REQUIRED)
find_package(ROOT REQUIRED Graf Gpad Hist RIO Tree)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++0x)
endif()


#-------------------
# set common include folder for module
#-------------------
set(PROJECT_RAW_IO_SOURCE ${PROJECT_BASE_DIR})
set(COMMON_INCLUDES ${PROJECT_RAW_IO_SOURCE}/modules/IO/RawIO/include ${PROJECT_RAW_IO_SOURCE}/modules/Base/Image/include ${PROJECT_RAW_IO_SOURCE}/modules/Plotting/Histograms/include )
message(STATUS "Common includes ${COMMON_INCLUDES}")
set(EXT_PROJECTS_DIR $ENV{HOME}/Software)


enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
set(GTEST_INCLUDE_DIRS ${EXT_PROJECTS_DIR}/gtest-1.7.0/include)
set(ROOT_INCLUDE_DIRS ${EXT_PROJECTS_DIR}/root-6.0.4/include)

set(GTEST_LIBS_DIR ${EXT_PROJECTS_DIR}/gtest-1.7.0/lib)
set(TEST_LIB_DIR ${PROJECT_RAW_IO_SOURCE}/build/lib/)

include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
include_directories(${ROOT_INCLUDE_DIRS})

#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cxx)
add_executable(${PROJECT_TEST_NAME} ${PROJECT_SOURCE_DIR}/stkImageHistogramUnitTest.cxx)
#add_dependencies(${PROJECT_TEST_NAME} googletest)



target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a)

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

#message(STATUS "ROOT Libs to link against: ${ROOT_LIBRARIES}")

target_link_libraries( ${PROJECT_TEST_NAME} ${ROOT_LIBRARIES})

target_link_libraries(${PROJECT_TEST_NAME} ${TEST_LIB_DIR}/libstkRawIO.so ${TEST_LIB_DIR}/libstkImage.so ${TEST_LIB_DIR}/libstkImageHistogram.so )

add_test(test1 ${PROJECT_TEST_NAME})

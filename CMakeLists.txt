cmake_minimum_required(VERSION 2.8)

project(FudanDNN)

find_package(Boost 1.55
	COMPONENTS
		unit_test_framework
	REQUIRED
)

if(Boost_FOUND)
	include_directories(
		${Boost_INCLUDE_DIRS} 
		${PROJECT_SOURCE_DIR}/src)
	link_directories(${Boost_LIBRARY_DIRS})
	add_definitions(-DBOOST_TEST_DYN_LINK)
else()
	message(FATAL_ERROR "Boost donesn't exsit or boost is too old!")
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src/fudandnn/core)
add_subdirectory(src/fudandnn/tests)
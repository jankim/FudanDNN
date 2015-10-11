cmake_minimum_required(VERSION 2.8)

project(FudanDNN)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/cmake")

set(FudanDNN_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src")
include_directories(${FudanDNN_INCLUDE_DIRS})

find_package(Boost 1.55
	COMPONENTS
		unit_test_framework
	REQUIRED
)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})
	add_definitions(-DBOOST_TEST_DYN_LINK)
else()
	message(FATAL_ERROR "Boost doesn't exist or boost is too old!")
endif()

option(GPU "GPU" OFF)

if(${GPU} STREQUAL "OpenCL")

	message(STATUS "Use OpenCL backends")

	find_package(OpenCL 1.2)

	if(OpenCL_FOUND) 
		find_package(ViennaCL)
		if(ViennaCL_FOUND)
	
			include_directories(${OpenCL_INCLUDE_DIRS})
			link_directories(${OpenCL_LIBRARIES})
	
			include_directories(${ViennaCL_INCLUDE_DIRS})
			add_definitions(-DFUDANDNN_GPU)
			add_definitions(-DFUDANDNN_GPU_OPENCL)
			add_definitions(-DVIENNACL_WITH_OPENCL)
		else()
			message("ViennaCL doesn't exist!")
		endif()	
	else()
		message(FATAL_ERROR "OpenCL doesn't exist or is too old! (At least 1.2)")
	endif()


elseif(${GPU} STREQUAL "Cuda")

	message(STATUS "Use Cuda backends")
	message(STATUS "Don't support Cuda now")

else()

	message(STATUS "Use CPU backends")

endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src/fudandnn/core)
add_subdirectory(src/fudandnn/tests)
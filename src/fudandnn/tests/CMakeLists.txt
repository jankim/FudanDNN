project(FudanDNN)

set (SRC_LIST
	fudandnn_test.cpp
	cnn_test.cpp)

add_executable(fudandnn_test ${SRC_LIST})

target_link_libraries(fudandnn_test ${Boost_LIBRARIES} fudandnn)

add_custom_command(TARGET fudandnn_test
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${EXECUTABLE_OUTPUT_PATH}/dataset
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/dataset ${EXECUTABLE_OUTPUT_PATH}/dataset
)
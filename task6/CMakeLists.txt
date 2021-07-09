cmake_minimum_required(VERSION 3.7)
project(main)

set(CMAKE_CXX_STANDARD 14)

set(TARGET unittest)
find_package(Threads REQUIRED)

set(GTEST_INCLUDE_DIRS "${SOURCE_DIR}/googletest/include")
set(GTEST_LIBRARY_DIRS "${BINARY_DIR}/lib")

set(TEST_SOURCES
	main.cpp
	map_json_to_struct.cpp
	map_struct_to_json.cpp
)

add_executable(${TARGET} ${TEST_SOURCES})
find_package(OpenCV REQUIRED)

#add_executable(OpenCV_Basics ${SOURCE_FILES})
#target_link_libraries(OpenCV_Basics )

target_compile_features(${TARGET} PRIVATE cxx_std_17)

target_include_directories(${TARGET} PRIVATE SYSTEM
	${CMAKE_SOURCE_DIR}/include
	${GTEST_INCLUDE_DIRS}
	${GMOCK_INCLUDE_DIRS}
)

#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${TARGET}
    ${OpenCV_LIBS}
)

add_test(
	NAME ${TARGET}
	COMMAND ${TARGET})

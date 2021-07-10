cmake_minimum_required(VERSION 3.7)
project(main)

set(CMAKE_CXX_STANDARD 14)

set(TARGET main.cpp)
add_executable(main ${TARGET})

find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_link_libraries(${PROJECT_NAME}  nlohmann_json::nlohmann_json)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Mosquitto REQUIRED IMPORTED_TARGET libmosquitto)
target_link_libraries(${PROJECT_NAME} PkgConfig::Mosquitto)
#=============
include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

find_package(Threads REQUIRED)

#target_compile_features(${TARGET} PRIVATE cxx_std_17)

include_directories(json-develop/include/nlohmann/)
include_directories(json-develop/include/)
#add_subdirectory( json-develop/ )

if(NOT NLOHMANNJSON_ROOT)
  set(NLOHMANNJSON_ROOT "${PROJECT_SOURCE_DIR}/lib/json")
endif()

add_library( ${TARGET} INTERFACE )

#target_include_directories(${TARGET} PRIVATE SYSTEM
#	${CMAKE_SOURCE_DIR}/include
#)

target_include_directories(
    #nlohmann_json
    ${TARGET}
  INTERFACE
    ${NLOHMANNJSON_ROOT}/include
)


# CMake generated Testfile for 
# Source directory: /home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_add_subdirectory
# Build directory: /home/s/Desktop/RTSoft/task6/doc/_deps/json-build/test/cmake_add_subdirectory
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_add_subdirectory_configure "/usr/bin/cmake" "-G" "Unix Makefiles" "-Dnlohmann_json_source=/home/s/Desktop/RTSoft/task6/doc/_deps/json-src" "/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_add_subdirectory/project")
set_tests_properties(cmake_add_subdirectory_configure PROPERTIES  FIXTURES_SETUP "cmake_add_subdirectory" _BACKTRACE_TRIPLES "/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_add_subdirectory/CMakeLists.txt;1;add_test;/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_add_subdirectory/CMakeLists.txt;0;")
add_test(cmake_add_subdirectory_build "/usr/bin/cmake" "--build" ".")
set_tests_properties(cmake_add_subdirectory_build PROPERTIES  FIXTURES_REQUIRED "cmake_add_subdirectory" _BACKTRACE_TRIPLES "/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_add_subdirectory/CMakeLists.txt;7;add_test;/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_add_subdirectory/CMakeLists.txt;0;")

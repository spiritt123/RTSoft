# CMake generated Testfile for 
# Source directory: /home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_import
# Build directory: /home/s/Desktop/RTSoft/task6/doc/_deps/json-build/test/cmake_import
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_import_configure "/usr/bin/cmake" "-G" "Unix Makefiles" "-A" "" "-Dnlohmann_json_DIR=/home/s/Desktop/RTSoft/task6/doc/_deps/json-build" "/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_import/project")
set_tests_properties(cmake_import_configure PROPERTIES  FIXTURES_SETUP "cmake_import" _BACKTRACE_TRIPLES "/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_import/CMakeLists.txt;1;add_test;/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_import/CMakeLists.txt;0;")
add_test(cmake_import_build "/usr/bin/cmake" "--build" ".")
set_tests_properties(cmake_import_build PROPERTIES  FIXTURES_REQUIRED "cmake_import" _BACKTRACE_TRIPLES "/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_import/CMakeLists.txt;8;add_test;/home/s/Desktop/RTSoft/task6/doc/_deps/json-src/test/cmake_import/CMakeLists.txt;0;")

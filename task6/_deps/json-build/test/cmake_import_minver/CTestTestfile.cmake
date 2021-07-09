# CMake generated Testfile for 
# Source directory: /home/s/Desktop/RTSoft/task6/_deps/json-src/test/cmake_import_minver
# Build directory: /home/s/Desktop/RTSoft/task6/_deps/json-build/test/cmake_import_minver
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cmake_import_minver_configure "/usr/bin/cmake" "-G" "Unix Makefiles" "-A" "" "-Dnlohmann_json_DIR=/home/s/Desktop/RTSoft/task6/_deps/json-build" "/home/s/Desktop/RTSoft/task6/_deps/json-src/test/cmake_import_minver/project")
set_tests_properties(cmake_import_minver_configure PROPERTIES  FIXTURES_SETUP "cmake_import_minver" _BACKTRACE_TRIPLES "/home/s/Desktop/RTSoft/task6/_deps/json-src/test/cmake_import_minver/CMakeLists.txt;1;add_test;/home/s/Desktop/RTSoft/task6/_deps/json-src/test/cmake_import_minver/CMakeLists.txt;0;")
add_test(cmake_import_minver_build "/usr/bin/cmake" "--build" ".")
set_tests_properties(cmake_import_minver_build PROPERTIES  FIXTURES_REQUIRED "cmake_import_minver" _BACKTRACE_TRIPLES "/home/s/Desktop/RTSoft/task6/_deps/json-src/test/cmake_import_minver/CMakeLists.txt;8;add_test;/home/s/Desktop/RTSoft/task6/_deps/json-src/test/cmake_import_minver/CMakeLists.txt;0;")

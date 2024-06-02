# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.7...3.29)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("FileFinder" VERSION 1.0 DESCRIPTION "A threaded file finder project" LANGUAGES CXX)

# Include library files.
#include_directories($(CMAKE_SOURCE_DIR)/include)
add_executable (file-finder "${CMAKE_SOURCE_DIR}/src/FileFinder.cpp" "src/FileScanner.cpp")
target_include_directories(file-finder PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_compile_features(file-finder PUBLIC cxx_std_20)
configure_file("${CMAKE_SOURCE_DIR}/.env" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET file-finder  PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
# add_executable(file-finder-tests "${CMAKE_SOURCE_DIR}/tests/test_a.cpp")
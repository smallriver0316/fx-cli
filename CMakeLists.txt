cmake_minimum_required(VERSION 3.16.3)

# it enable to refer project name as ${PROJECT_NAME}
project(fx
  VERSION 1.0
  DESCRIPTION "CLI tool of converting number to foreign country style"
  LANGUAGES CXX)

# C++ version
set(CMAKE_CXX_STANDARD 17)
# output error when specified C++ version is unavailable
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ...without compiler extensions like gnu++11
set(CMAKE_CXX_EXTENSIONS OFF)

set(DEFAULT_BUILD_TYPE "Debug")

add_subdirectory(src)

include(cmake/CLI11.cmake)
include(cmake/cpr.cmake)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "Including googletest and tests in non-Release build")
  enable_testing()
  include(cmake/gtest.cmake)
  add_subdirectory(tests)
endif()

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

# define the executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE CLI11::CLI11)
target_link_libraries(${PROJECT_NAME} PRIVATE libfx)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# set compiler options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

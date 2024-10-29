cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project( "3DReconstruction" VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

option(ENABLE_TESTING "Enable a Unit Testing build." ON)
option(ENABLE_COVERAGE "Enable a Code Coverage build." OFF)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)
option(ENABLE_CLANG_FORMAT "Enable to add clang-format." OFF)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
include(External-OpenCV)

add_subdirectory(tests)
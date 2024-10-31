cmake_minimum_required(VERSION 3.22.1)

include(ExternalProject)

set(EIGEN_INSTALL_DIR ${CMAKE_BINARY_DIR}/eigen-install)
set(CMAKE_PREFIX_PATH ${EIGEN_INSTALL_DIR})

find_package (Eigen3)
if(${EIGEN3_FOUND})
    message(STATUS "Eigen3 found: ${EIGEN_INSTALL_DIR}")
else()
    message(STATUS "Eigen3 not found. Downloading and building from source...")
    ExternalProject_Add(
        eigen
        URL  https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
        SOURCE_DIR "${CMAKE_BINARY_DIR}/eigen-src"
        BINARY_DIR "${CMAKE_BINARY_DIR}/eigen-build"
        INSTALL_DIR "${EIGEN_INSTALL_DIR}"
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=Release
    )
    include_directories(SYSTEM ${EIGEN_INCLUDE_DIR})
endif()
cmake_minimum_required(VERSION 3.22.1)

if(NOT OpenCV_TAG)
    set(OpenCV_TAG "4.10.0")
endif()

find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    message(STATUS "OpenCV found: ${OpenCV_DIR}")
else()
    message(WARNING "OpenCV not found. Building OpenCV from source.")

    include(ExternalProject)
    ExternalProject_Add(OpenCV
        GIT_REPOSITORY "https://github.com/opencv/opencv.git"
        GIT_TAG "${OpenCV_TAG}"
        SOURCE_DIR ${CMAKE_BINARY_DIR}/opencv
        BINARY_DIR ${CMAKE_BINARY_DIR}/opencv-build
        CMAKE_ARGS
            -DBUILD_DOCS=FALSE
            -DBUILD_EXAMPLES=FALSE
            -DBUILD_TESTS=FALSE
            -DBUILD_opencv_apps=FALSE
            -DBUILD_SHARED_LIBS=TRUE
            -DWITH_CUDA=FALSE
            -DWITH_FFMPEG=FALSE
            -DBUILD_PERF_TESTS=FALSE
            -DBUILD_opencv_java=OFF
            -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/opencv
            -DOPENCV_EXTRA_MODULES_PATH=./opencv_contrib/modules/xfeatures2d
    )
    
    set(OpenCV_DIR ${CMAKE_BINARY_DIR}/opencv)
    include_directories(${OpenCV_DIR}/include)
    link_directories(${OpenCV_DIR}/lib)
endif()
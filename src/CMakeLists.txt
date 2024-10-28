cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Testing)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
option(USE_CONAN "Whether to use Conan." ON)
option(USE_VCPKG "Whether to use VCPKG." OFF)
option(USE_CPM   "Whether to use CPM."   OFF)


# Specify the directory containing VTK's include files
set(VTK_INCLUDE_DIR "C:/Program Files/VTK-9.3.1/src")
set(VTK_DIR "C:/Program Files/VTK-9.3.1/build")
# Specify the directory containing VTK's library files
set(VTK_LIB_DIR "C:/Program Files/VTK-9.3.1/build/lib")
link_directories("C:/Program Files/VTK-9.3.1")
# Set the include directory
include_directories(${VTK_INCLUDE_DIR})

find_package(VTK REQUIRED)
find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  FiltersSources
  IOImage
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  RenderingUI
  IOPLY
  CommonDataModel
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Testing: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(testvtk  testpclvtk.cpp)
target_link_libraries(testvtk  PRIVATE ${VTK_LIBRARIES})
vtk_module_autoinit(
  TARGETS testvtk
  MODULES ${VTK_LIBRARIES}
)
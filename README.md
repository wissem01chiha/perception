<div align="center">

## Robotic Perception Library
A fully templated C++ implementation of general-use algorithms for robotic perception and visual servoing.



![C++](https://img.shields.io/badge/C%2B%2B-11%2F14%2F17%2F20%2F23-blue)
![License](https://img.shields.io/github/license/franneck94/CppProjectTemplate)
![Linux Build](https://github.com/franneck94/CppProjectTemplate/workflows/Ubuntu%20CI%20Test/badge.svg)

</div>

---

### Goals
 RPL project has the following goals:
 *  Provide optimized and flexible modules for collision prediction and detection  for collaborative robotic applications.
 * Feature extraction from camera images and/or sensors data types. 
 * Environment reconstruction and processing, trajectory planning in unconstrained worlds. 
 * Robust control strategies based on visual input.
 * A set of fuzzy relations between solid objects, and develops, and a set of human-like control algorithms. 

---
 
 
This is a template for modern C++ projects.
What you get is:

- Library, executable and test code separated in distinct folders
- Use of modern CMake for building and compiling
- External libraries installed and managed by
  - [CPM](https://github.com/cpm-cmake/CPM.cmake) Package Manager **OR**
  - [Conan](https://conan.io/) Package Manager **OR**
  - [VCPKG](https://github.com/microsoft/vcpkg) Package Manager
- Unit testing using [Catch2](https://github.com/catchorg/Catch2) v2
- General purpose libraries: [JSON](https://github.com/nlohmann/json), [spdlog](https://github.com/gabime/spdlog), [cxxopts](https://github.com/jarro2783/cxxopts) and [fmt](https://github.com/fmtlib/fmt)
- Continuous integration testing with Github Actions and [pre-commit](https://pre-commit.com/)
- Code documentation with [Doxygen](https://doxygen.nl/) and [Github Pages](https://franneck94.github.io/CppProjectTemplate/)
- Tooling: Clang-Format, Cmake-Format, Clang-tidy, Sanitizers


## Software Requirements

- CMake 3.21+
- GNU Makefile
- Doxygen
- Conan or VCPKG
- MSVC 2017 (or higher), G++9 (or higher), Clang++9 (or higher)
- Optional: Code Coverage (only on GNU|Clang): gcovr
- Optional: Makefile, Doxygen, Conan, VCPKG

## Building

First, clone this repo and do the preliminary work:

```shell
git clone --recursive https://github.com/franneck94/CppProjectTemplate
mkdir build
```

- App Executable

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target main
cd app
./main
```

- Unit testing

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE="Debug"
cmake --build build --config Debug
cd build
ctest .
```

- Documentation

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target docs
```

- Code Coverage (Unix only)

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=On
cmake --build build --config Debug --target coverage -j4
cd build
ctest .
```

For more info about CMake see [here](./README_cmake.md).
### Testing

### Datasets

- **[Visual Servoing Dataset](#https://github.com/RauldeQueirozMendes/VSDataset/tree/main)**, *E. G. Ribeiro, R. Q. Mendes and V. Grassi Jr*  


###  References

- **Real-Time Deep Learning Approach to Visual Servo Control and Grasp Detection for Autonomous Robotic Manipulation**, *E. G. Ribeiro, R. Q. Mendes, V. Grassi Jr*, Elsevier's Robotics and Autonomous Systems, 2021
*Robotics and Autonomous Systems*, Elsevier, 2021. DOI: [10.1016/j.robot.2021.103757](https://doi.org/10.1016/j.robot.2021.103757) 

- **Training deep neuralnetworks for visual servoing**, *Q. Bateux, E. Marchand, J. Leitner, F. Chaumette, P. Corke*, ICRA 2018

- **Classical and Deep Learning based Visual Servoing Systems: a Survey on State of the Art**, *Z.Machkour, D.Ortiz-Arroyo, P.Durdevic*, 2021

- **Introductory Techniques for 3-D Computer Vision**, *Emanuele Trucco, Alessandro Verri*, 1998

- **Three-dimensional computer vision a geometric viewpoint**, *Olivier Faugeras*, 1993

-**Robot Vision**,*Berthold K.P. Horn*, 1987

### Contributing
please see the [CONTRIBUTING](CONTRIBUTING.md) guide for more informations 

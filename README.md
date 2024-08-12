<div align="center">

## Robotic Perception Library
A templated C++ implementation of robotic perception and visual servoing algorithms.

</div>
---

### Requirements
The project relay on many external denadancy some of thelm are manged with populer packages manger like:
  - [CPM](https://github.com/cpm-cmake/CPM.cmake) 
  - [Conan](https://conan.io/) Package Manager 
  - [VCPKG](https://github.com/microsoft/vcpkg) Package Manager

and other small size header only libs are housed along the sources 

- General purpose libraries: [JSON](https://github.com/nlohmann/json), [spdlog](https://github.com/gabime/spdlog), [cxxopts](https://github.com/jarro2783/cxxopts) and [fmt](https://github.com/fmtlib/fmt)
 

## Software Requirements

- CMake 3.21+
- MSVC 2017 (or higher)
- GNU Makefile

- Optional: Makefile, Doxygen, Conan or VCPKG

## Build Exemples

First, clone this repository :

```shell
git clone  https://github.com/wissem01chiha/RPL
```

- Build all the project exmeples: 

```shell
cd Build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target main
```

- Unit testing

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE="Debug"
cmake --Build build --config Debug
cd Build
ctest .
```

- Documentation

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Rlease ..
cmake --build . --config Rlease --target docs
```

- Code Coverage (Unix only)

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=On
cmake --build build --config Debug --target coverage -j4
cd build
ctest .
```

For more info about CMake see [here](./README_cmake.md).

### Build Tests
the official test framwork used is Catch2  [Catch2](https://github.com/catchorg/Catch2) 
Building test :
warning : if VTK is complied for Debug model we recommned compiling tests and exemples into debug mode
replace Release with debug in the above commands 
```shell
cd Build
cmake ../Testing  -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Datasets

- **Visual Servoing Dataset**, *E. G. Ribeiro, R. Q. Mendes and V. Grassi Jr* 

###  References
- **Real-Time Deep Learning Approach to Visual Servo Control and Grasp Detection for Autonomous Robotic Manipulation**, *E. G. Ribeiro, R. Q. Mendes, V. Grassi Jr*, Elsevier's Robotics and Autonomous Systems, 2021
*Robotics and Autonomous Systems*, Elsevier, 2021.
- **Training deep neuralnetworks for visual servoing**, *Q. Bateux, E. Marchand, J. Leitner, F. Chaumette, P. Corke*, ICRA 2018
- **Classical and Deep Learning based Visual Servoing Systems: a Survey on State of the Art**, *Z.Machkour, D.Ortiz-Arroyo, P.Durdevic*, 2021
- **Introductory Techniques for 3-D Computer Vision**, *Emanuele Trucco, Alessandro Verri*, 1998
- **Three-dimensional computer vision a geometric viewpoint**, *Olivier Faugeras*, 1993
- **Robot Vision**, *Berthold K.P. Horn*, 1987

### Contributing
see the [CHANGELOGS](CONTRIBUTING.md) guide.

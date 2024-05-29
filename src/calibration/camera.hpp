#pragma once
#include<cmath>
#include <Eigen/Dense>
using namespace Eigen;
 
namespace calibration
{

template<typename T>
class Camera
{
private:
    Matrix<T, 3, 3> R;
    Matrix<T, 3, 1>   T;
    T     aspectRatio; // sy/sx 
    T k1; // radial distoration coefficent
    T fx; // length in effective horizontal pixel size, focal length  
    T ox, oy ; // image center coordiantes 

public:

    // Constructor 
    Camera(/* args */);

    ~Camera();
};





} // namespace calibration
    
    
 

 








template <typename T>
inline calibration::Camera<T>::Camera()
{
}



template <typename T>
inline calibration::Camera<T>::~Camera()
{
}

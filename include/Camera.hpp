#pragma once 

#include <vector> 
#include <Eigen/Core>
#include <Eigen/Dense>
#include <loguru/loguru.hpp>

template<typename T>
class Camera {
public:
    // default constructor
    Camera();

    // constructor with focal length
    Camera(const T& f);

    // constructor with focal length and pixel dimensions
    Camera(const T &f,const T &kx, const T &ky);

    // constructor with calibration matrix
    Camera(Eigen::Matrix3<T> C);

    // constructor with projection and a given calibration matrix
    Camera(Eigen::Matrix<T,3 ,4> P, Eigen::Matrix3<T> C);

    // returns the projection matrix filled with actual parameters
    Eigen::Matrix<T, 3, 4> getProjectionMatrix() const;

    // returns the calibration matrix
    Eigen::Matrix3<T> getCalibrationMatrix() const;

    // returns the rotation matrix
    Eigen::Matrix3<T> getRotationMatrix() const;

    // captures a point in homogeneous coordinates and maps it to the image frame
    Eigen::Vector3<T> capture(Eigen::Vector4<T> point) const;

    // captures a point in euclidian space and maps it to the image frame
    Eigen::Vector2<T> capture(Eigen::Vector3<T> point) const;

    // updates the camera view via homogeneous transformation (rotation)
    void updateView(const Eigen::Matrix3<T>& R);

    // updates the camera view via translation
    void updateView(const Eigen::Vector3<T>& t);

    // updates the camera view with rotation and translation
    void updateView(const Eigen::Matrix3<T>& R, const Eigen::Vector3<T>& t);

    // computes the error between the actual homogonus transformation and the given one 
    // the error on rotations is R1^{T}*R2 the translation error is t2-t1
    Eigen::Matrix4<T> computeHomogeneousErrorMatrix(const Eigen::Matrix4<T>& H) const;

    // computes the back-projection of a 2D point with a depth value
    // use homogonus coordinates use the pseudo inverse of Projection matrix
    Eigen::Vector4<T> computeBackProjection(const Eigen::Vector3<T>& x, T depth) const;

    // use euclidian coordinates 
    Eigen::Vector3<T> computeBackProjection(const Eigen::Vector2<T>& x, T depth) const;

    // update the focal length 
    void setFocalLength(const T &f_);

    //update the image center coordinntes 
    void setPrincipalPoint(const T &u0_,const T &v0_);

    // updates pixel dims along x and y
    void setPixelDimensions(const T &kx_,const T &ky_);

    T getFocalLength() const;
    Eigen::Vector2<T> getPrincipalPoint() const;
    Eigen::Vector2<T> getPixelDimensions() const;

private:
    Eigen::Matrix3<T> C;               // Camera calibration matrix
    Eigen::Matrix<T, 3, 4> P;          // Camera projection matrix
    Eigen::Vector3<T> t;               // Translation vector
    Eigen::Matrix3<T> R;               // Rotation matrix
    T aspectRatio;                     // Aspect ratio
    T xAspectRatio;                    // Pixel aspect ratio (vertical)
    T yAspectRatio;                    // Pixel aspect ratio (horizontal)
    T focalLength;                     // Focal length
    T kx;                              // Pixels per length in x
    T ky;                              // Pixels per length in y
    T u0;                              // Image center x-coordinate
    T v0;                              // Image center y-coordinate
};

using CameraD = Camera<double>; 
using CameraF = Camera<float>;   
using CameraLD = Camera<long double>;
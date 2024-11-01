#include "Camera.hpp"

template <typename T>
Camera<T>::Camera()
{                                     
    focalLength = std::static_cast<T>(1.0); 
    kx = std::static_cast<T>(1.0);
    ky = std::static_cast<T>(1.0);  
    xAspectRatio = kx * focalLength;
    yAspectRatio = -ky * focalLength;                     
    aspectRatio = ky / kx;   
    u0 = std::static_cast<T>(0.0);                               
    v0 = std::static_cast<T>(0.0); 
    C =  Eigen::Matrix3<T>::Identity();
    t.setZero();
    R = Eigen::Matrix3<T>::Identity();
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));                          
}

template <typename T>
Camera<T>::Camera(const T& f)
{
    CHECK_F(f != nullptr, "Focal length variable pointer is null");
    CHECK_F(f > std::static_cast<T>(0) , "Focal length should be positive");
    focalLength = f;
    kx = std::static_cast<T>(1.0);
    ky = std::static_cast<T>(1.0);  
    xAspectRatio = kx * focalLength;
    yAspectRatio = -ky * focalLength;                     
    aspectRatio  = ky / kx;
    u0 = std::static_cast<T>(0.0);                               
    v0 = std::static_cast<T>(0.0); 
    C << xAspectRatio, std::static_cast<T>(0),u0,
        std::static_cast<T>(0), yAspectRatio,v0,
        std::static_cast<T>(0), std::static_cast<T>(0), std::static_cast<T>(1);
    t.setZero();
    R = Eigen::Matrix3<T>::Identity();
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));                              
}

template <typename T>
Camera<T>::Camera(const T &f,const T &kx, const T &ky)
{   
    CHECK_F(f > std::static_cast<T>(0) , "Focal length should be positive");
    CHECK_F(kx > std::static_cast<T>(0) , "x-Resolution should be positive");
    CHECK_F(ky > std::static_cast<T>(0) , "y-Resolution should be positive");
    focalLength = f;
    kx = ky;
    ky = kx;
    xAspectRatio = kx * focalLength;
    yAspectRatio = -ky * focalLength;                     
    aspectRatio  = ky / kx;
    u0 = std::static_cast<T>(0.0);                               
    v0 = std::static_cast<T>(0.0); 
    C << xAspectRatio, std::static_cast<T>(0),u0,
        std::static_cast<T>(0), yAspectRatio,v0,
        std::static_cast<T>(0), std::static_cast<T>(0), std::static_cast<T>(1);
    t.setZero();
    R = Eigen::Matrix3<T>::Identity();
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));
}

template <typename T>
Camera<T>::Camera(Eigen::Matrix3<T> C)
{
    xAspectRatio = C(0,0);
    yAspectRatio = C(1,1);
    u0 = C(0,2);                               
    v0 = C(1,2);
    aspectRatio = yAspectRatio / xAspectRatio; // if this is equal to 1 then fx == fy
    if(aspectRatio == std::static_cast<T>(1)){
        focalLength = xAspectRatio;
        kx = std::static_cast<T>(1.0);
        ky = std::static_cast<T>(1.0);
    }
    t.setZero();
    R = Eigen::Matrix3<T>::Identity();
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));
}

template <typename T>
Camera<T>::Camera(Eigen::Matrix<T, 3, 4> P, Eigen::Matrix3<T> C)
{
    xAspectRatio = C(0,0);
    yAspectRatio = C(1,1);
    aspectRatio = yAspectRatio / xAspectRatio; 
    if(aspectRatio == std::static_cast<T>(1)){
        focalLength = xAspectRatio;
        kx = std::static_cast<T>(1.0);
        ky = std::static_cast<T>(1.0);
    }
    u0 = C(0,2);                               
    v0 = C(1,2);
    R = P.leftCols<3>();
    t = P.col(3);
}

template <typename T>
Eigen::Matrix<T, 3, 4> Camera<T>::getProjectionMatrix() const
{
    return P;
}

template <typename T>
Eigen::Matrix3<T> Camera<T>::getCalibrationMatrix() const
{
    return C;
}

template <typename T>
Eigen::Matrix3<T> Camera<T>::getRotationMatrix() const
{
    return R;
}

template <typename T>
Eigen::Vector3<T> Camera<T>::capture(Eigen::Vector4<T> point) const
{
    return P * point;
}

template <typename T>
Eigen::Vector2<T> Camera<T>::capture(Eigen::Vector3<T> point) const
{
    Eigen::Vector4<T> homogeneousPoint;
    homogeneousPoint << point, std::static_cast<T>(1); 
    Eigen::Vector4<T> projectedPoint = P * homogeneousPoint;
    if (projectedPoint(2) != T(0)) {
        return Eigen::Vector2<T>(projectedPoint(0) / projectedPoint(2), projectedPoint(1) / projectedPoint(2));
    } else { // the case where the point is at infinity
        return Eigen::Vector2<T>(0, 0); 
    }
}

template <typename T>
Eigen::Vector4<T> Camera<T>::computeBackProjection(const Eigen::Vector3<T> &x, T depth) const
{
    Eigen::Matrix<T, 4, 1> x_homogeneous;
    x_homogeneous << x(0), x(1), std::static_cast<T>(1), std::static_cast<T>(1);
    x_homogeneous(2) = depth;
    Eigen::Matrix<T, 4, 3> P_pinv = P.transpose() * (P * P.transpose()).inverse();
    Eigen::Matrix<T, 4, 1> X = P_pinv * x_homogeneous;

    return X;
}

template <typename T>
Eigen::Vector3<T> Camera<T>::computeBackProjection(const Eigen::Vector2<T> &x, T depth) const
{
    Eigen::Matrix<T, 4, 1> x_homogeneous;
    x_homogeneous << x(0), x(1), 1, depth;
    Eigen::Matrix<T, 4, 3> P_pinv = P.transpose() * (P * P.transpose()).inverse();
    Eigen::Matrix<T, 4, 1> X = P_pinv * x_homogeneous;

    return X.head<3>() / X(3);
}

template <typename T>
void Camera<T>::setFocalLength(const T &f_)
{
    CHECK_F(f_ > std::static_cast<T>(0) , "Focal length should be positive");
    focalLength = f_;
    xAspectRatio = kx * focalLength;
    yAspectRatio = -ky * focalLength;
    C << xAspectRatio, std::static_cast<T>(0),u0,
        std::static_cast<T>(0), yAspectRatio, v0,
        std::static_cast<T>(0), std::static_cast<T>(0), std::static_cast<T>(1);
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));
}

template <typename T>
void Camera<T>::setPrincipalPoint(const T &u0_,const T &v0_)
{
    CHECK_F(u0 > std::static_cast<T>(0) , "Image width should be positive");
    CHECK_F(v0 > std::static_cast<T>(0) , "Image length should be positive");
    u0 = u0_;
    v0 = v0_;
    C << xAspectRatio, std::static_cast<T>(0),u0,
            std::static_cast<T>(0), yAspectRatio, v0,
            std::static_cast<T>(0), std::static_cast<T>(0), std::static_cast<T>(1);
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));
}

template <typename T>
void Camera<T>::setPixelDimensions(const T &kx,const T &ky)
{
    kx = kx_;
    ky = ky_;
}

template <typename T>
Eigen::Vector2<T> Camera<T>::getPrincipalPoint() const
{
    return Eigen::Vector2<T>(u0,v0);
}

template <typename T>
T Camera<T>::getFocalLength() const
{
    return focalLength;
}

template <typename T>
Eigen::Vector2<T> Camera<T>::getPixelDimensions() const
{
    Eigen::Vector2<T> v = Eigen::Vector2<T>(kx, ky);
    return v;
}

template <typename T>
void Camera<T>::updateView(const Eigen::Matrix3<T> &R)
{
    R = R_;
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));
}

template <typename T>
void Camera<T>::updateView(const Eigen::Vector3<T> &t)
{
    t = t_;
    P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));
}

template <typename T>
void Camera<T>::updateView(const Eigen::Matrix3<T> &R_, const Eigen::Vector3<T> &t_)
{
        R = R_;
        t = t_;
        P = C*(R.col(0).homogeneous()*t(0)+R.col(1).homogeneous()*t(1)+R.col(2).homogeneous()*t(2));
}

template <typename T>
Eigen::Matrix4<T> Camera<T>::computeHomogeneousErrorMatrix(const Eigen::Matrix4<T> &H) const
{
    Eigen::Matrix3<T> R2 = H.block<3, 3>(0, 0);
    Eigen::Vector3<T> t2 = H.block<3, 1>(0, 3);
    
    Eigen::Matrix4<T> Hrr;
    Hrr << R2.transpose(), t2 - t,
           0, 0, 0, 1;  

    return Hrr;
}
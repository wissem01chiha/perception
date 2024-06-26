#pragma once
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

namespace geometry
{
    
template <class Precision= double >
struct Point3
{
    Precision x, y, z;

    // constructor
    Point3(Precision x_, Precision y_, Precision z_) : x(x_), y(y_), z(z_){}

    // return the point as an Eigen vector
    Matrix<Precision, 3, 1> toEigenVector() const{
        return Vector3<Precision>(x, y, z);
    }

    // create a Point3d from an Eigen vector
    static Point3 fromEigenVector(const Matrix<Precision, 3, 1>& vec){
        return Point3d(vec.x(), vec.y(), vec.z());
    }

    // Addition
    Point3 operator+(const Point3& other) const {
        return Point3d(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction
    Point3 operator-(const Point3& other) const {
        return Point3d(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Point3 operator*(Precision scalar) const {
        return Point3d(x * scalar, y * scalar, z * scalar);
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Point3& point) {
        return is >> point.x >> point.y >> point.z;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Point3& point) {
        return os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    }

    // Comparison operator ==
    bool operator==(const Point3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Comparison operator !=
    bool operator!=(const Point3& other) const {
        return !(*this == other);
    }
    
    // Distance to another point
    Precision distanceTo(const Point3& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y) +
                         (z - other.z) * (z - other.z));
    }

    // Normalize the point  
    Point3 normalize() const {
        Precision magnitude = std::sqrt(x * x + y * y + z * z);
        return Point3(x / magnitude, y / magnitude, z / magnitude);
    }

    // Dot product with another point
    Precision dot(const Point3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product with another point
    Point3 cross(const Point3& other) const {
        return Point3(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }
};

template<class Precision = double >
struct Point2 {
    Precision x, y;

    // Default constructor, Origin referance point
    Point2() : x(Precision(0)), y(Precision(0)) {}

    // Main constructor 
    Point2(Precision x_, Precision y_) : x(x_), y(y_) {}

    // Return the point as an Eigen vector
    Matrix<Precision, 2, 1> toEigenVector() const {
        return  Matrix<Precision, 2, 1>(x, y);
    }

    // Create a Point2d from an Eigen vector
    static Point2 fromEigenVector(const Matrix<Precision, 2, 1>& vec) {
        return Point2(vec.x(), vec.y());
    }

    // Addition
    Point2 operator+(const Point2& other) const {
        return Point2d(x + other.x, y + other.y);
    }

    // Subtraction
    Point2 operator-(const Point2& other) const {
        return Point2(x - other.x, y - other.y);
    }

    // Scalar multiplication
    Point2 operator*(Precision scalar) const {
        return Point2d(x * scalar, y * scalar);
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Point2& point) {
        return is >> point.x >> point.y;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Point2& point) {
        return os << "(" << point.x << ", " << point.y << ")";
    }

    // Comparison operator ==
    bool operator==(const Point2& other) const {
        return x == other.x && y == other.y;
    }

    // Comparison operator !=
    bool operator!=(const Point2& other) const {
        return !(*this == other);
    }

    // Distance to another point
    Precision distanceTo(const Point2& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y));
    }

    // Normalize the point  
    Point2 normalized() const {
        Precision magnitude = std::sqrt(x * x + y * y);
        return Point2(x / magnitude, y / magnitude);
    }

    // Dot product with another point
    Precision dot(const Point2& other) const {
        return x * other.x + y * other.y;
    }
};

// this struct is used to reprsent a moving point respect to time 
template<class Precision = double>
struct Point4 {

    Precision x, y, z, t;

    // Default constructor
    Point4() : x(Precision(0)), y(Precision(0)), z(Precision(0)), t(Precision(0)){}

    // Fixed point 
    Point4(Precision x_, Precision y_, Precision z_):x(x_),y(y_),z(z_), t(Precision(0)){}

    // Full Constructor
    Point4(Precision x_, Precision y_, Precision z_, Precision t_):x(x_), y(y_),z(z_), t(t_) {}

    // Return the point as an Eigen vector
    Matrix<Precision, 4, 1> toEigenVector() const {
        return Matrix<Precision, 4, 1>(x, y, z, t);
    }

    // Create a Point4 from an Eigen vector
    static Point4 fromEigenVector(const Matrix<Precision, 4, 1>& vec) {
        return Point4(vec.x(), vec.y(), vec.z(), vec(3));
    }

    // Addition
    Point4 operator+(const Point4& other) const {
        return Point4(x + other.x, y + other.y, z + other.z, t + other.t);
    }

    // Subtraction
    Point4 operator-(const Point4& other) const {
        return Point4(x - other.x, y - other.y, z - other.z, t - other.t);
    }

    // Scalar multiplication
    Point4 operator*(Precision scalar) const {
        return Point4(x * scalar, y * scalar, z * scalar, t * scalar);
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Point4& point) {
        return is >> point.x >> point.y >> point.z >> point.t;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Point4& point) {
        return os << "(" << point.x << ", " << point.y << ", " << point.z << ", " << point.t << ")";
    }

    // Comparison operator ==
    bool operator==(const Point4& other) const {
        return x == other.x && y == other.y && z == other.z && t == other.t;
    }

    // Comparison operator !=
    bool operator!=(const Point4& other) const {
        return !(*this == other);
    }

    // Distance to another point
    Precision distanceTo(const Point4& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y) +
                         (z - other.z) * (z - other.z) +
                         (t - other.t) * (t - other.t));
    }

    // Normalize the point  
    Point4 normalized() const {
        Precision magnitude = std::sqrt(x * x + y * y + z * z + t * t);
        return Point4(x / magnitude, y / magnitude, z / magnitude, t / magnitude);
    }

    // Dot product with another point
    Precision dot(const Point4& other) const {
        return x * other.x + y * other.y + z * other.z + t * other.t;
    }
};

typedef Point2<double> Point2d;
typedef Point2<float>  Point2f;
typedef Point3<double> Point3d;
typedef Point3<float>  Point3f;
typedef Point4<double> Point4d;
typedef Point4<float>  Point4f;

}; // namespace geometry
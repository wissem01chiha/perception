#pragma once
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

namespace geometry
{
    
template<typename T>
struct Point3d
{
    T x, y, z;

    // constructor
    Point3d(T x_, T y_, T z_) : x(x_), y(y_), z(z_){}

    // return the point as an Eigen vector
    Matrix<T, 3, 1> toEigenVector() const{
        return Vector3d(x, y, z);
    }

    // create a Point3d from an Eigen vector
    static Point3d fromEigenVector(const Matrix<T, 3, 1>& vec){
        return Point3d(vec.x(), vec.y(), vec.z());
    }

    // Addition
    Point3d operator+(const Point3d& other) const {
        return Point3d(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction
    Point3d operator-(const Point3d& other) const {
        return Point3d(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Point3d operator*(T scalar) const {
        return Point3d(x * scalar, y * scalar, z * scalar);
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Point3d& point) {
        return is >> point.x >> point.y >> point.z;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Point3d& point) {
        return os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    }

    // Comparison operator ==
    bool operator==(const Point3d& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Comparison operator !=
    bool operator!=(const Point3d& other) const {
        return !(*this == other);
    }
    
    // Distance to another point
    T distanceTo(const Point3d& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y) +
                         (z - other.z) * (z - other.z));
    }

    // Normalize the point  
    Point3d normalize() const {
        T magnitude = std::sqrt(x * x + y * y + z * z);
        return Point3d(x / magnitude, y / magnitude, z / magnitude);
    }

    // Dot product with another point
    T dot(const Point3d& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product with another point
    Point3d cross(const Point3d& other) const {
        return Point3d(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }
};

template<typename T>
struct Point2d {
    T x, y;

    // Constructor
    Point2d() : x(T(0)), y(T(0)) {}

    Point2d(T x_, T y_) : x(x_), y(y_) {}

    // Return the point as an Eigen vector
    Matrix<T, 2, 1> toEigenVector() const {
        return Eigen::Matrix<T, 2, 1>(x, y);
    }

    // Create a Point2d from an Eigen vector
    static Point2d fromEigenVector(const Eigen::Matrix<T, 2, 1>& vec) {
        return Point2d(vec.x(), vec.y());
    }

    // Addition
    Point2d operator+(const Point2d& other) const {
        return Point2d(x + other.x, y + other.y);
    }

    // Subtraction
    Point2d operator-(const Point2d& other) const {
        return Point2d(x - other.x, y - other.y);
    }

    // Scalar multiplication
    Point2d operator*(T scalar) const {
        return Point2d(x * scalar, y * scalar);
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Point2d& point) {
        return is >> point.x >> point.y;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Point2d& point) {
        return os << "(" << point.x << ", " << point.y << ")";
    }

    // Comparison operator ==
    bool operator==(const Point2d& other) const {
        return x == other.x && y == other.y;
    }

    // Comparison operator !=
    bool operator!=(const Point2d& other) const {
        return !(*this == other);
    }

    // Distance to another point
    T distanceTo(const Point2d& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y));
    }

    // Normalize the point  
    Point2d normalized() const {
        T magnitude = std::sqrt(x * x + y * y);
        return Point2d(x / magnitude, y / magnitude);
    }

    // Dot product with another point
    T dot(const Point2d& other) const {
        return x * other.x + y * other.y;
    }
};

template<typename T>
struct Point4d {
    T x, y, z, t;

    // Constructor
    Point4d() : x(T(0)), y(T(0)), z(T(0)), t(T(0)) {}

    Point4d(T x_, T y_, T z_, T t_) : x(x_), y(y_), z(z_), t(t_) {}

    // Return the point as an Eigen vector
    Matrix<T, 4, 1> toEigenVector() const {
        return Eigen::Matrix<T, 4, 1>(x, y, z, t);
    }

    // Create a Point4d from an Eigen vector
    static Point4d fromEigenVector(const Eigen::Matrix<T, 4, 1>& vec) {
        return Point4d(vec.x(), vec.y(), vec.z(), vec(3));
    }

    // Addition
    Point4d operator+(const Point4d& other) const {
        return Point4d(x + other.x, y + other.y, z + other.z, t + other.t);
    }

    // Subtraction
    Point4d operator-(const Point4d& other) const {
        return Point4d(x - other.x, y - other.y, z - other.z, t - other.t);
    }

    // Scalar multiplication
    Point4d operator*(T scalar) const {
        return Point4d(x * scalar, y * scalar, z * scalar, t * scalar);
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, Point4d& point) {
        return is >> point.x >> point.y >> point.z >> point.t;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Point4d& point) {
        return os << "(" << point.x << ", " << point.y << ", " << point.z << ", " << point.t << ")";
    }

    // Comparison operator ==
    bool operator==(const Point4d& other) const {
        return x == other.x && y == other.y && z == other.z && t == other.t;
    }

    // Comparison operator !=
    bool operator!=(const Point4d& other) const {
        return !(*this == other);
    }

    // Distance to another point
    T distanceTo(const Point4d& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y) +
                         (z - other.z) * (z - other.z) +
                         (t - other.t) * (t - other.t));
    }

    // Normalize the point  
    Point4d normalized() const {
        T magnitude = std::sqrt(x * x + y * y + z * z + t * t);
        return Point4d(x / magnitude, y / magnitude, z / magnitude, t / magnitude);
    }

    // Dot product with another point
    T dot(const Point4d& other) const {
        return x * other.x + y * other.y + z * other.z + t * other.t;
    }
};
} // namespace geometry
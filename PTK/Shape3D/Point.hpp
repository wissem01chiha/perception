#pragma once

#include <cmath>
#include <complex>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <Eigen/Dense>

using namespace Eigen;

namespace ptk { 

template <typename T>
struct Point3 {

    T x, y, z;

    // Default constructor
    Point3(T x_, T y_, T z_) : x(x_), y(y_), z(z_){}

    // return the point as an Eigen vector
    Matrix<T, 3, 1> toEigenVector() const{
        return Vector3<T>(x, y, z);
    };

    // create a Point3d from an Eigen vector
    static Point3 fromEigenVector(const Matrix<T, 3, 1>& vec){
        return Point3d(vec.x(), vec.y(), vec.z());
    };

    // addition
    Point3 operator+(const Point3& other) const {
        return Point3d(x + other.x, y + other.y, z + other.z);
    };

    // subtraction
    Point3 operator-(const Point3& other) const {
        return Point3d(x - other.x, y - other.y, z - other.z);
    };

    // scalar multiplication
    Point3 operator*(T scalar) const {
        return Point3d(x * scalar, y * scalar, z * scalar);
    };

    // input operator
    friend std::istream& operator>>(std::istream& is, Point3& point) {
        return is >> point.x >> point.y >> point.z;
    };

    // output operator
    friend std::ostream& operator<<(std::ostream& os, const Point3& point) {
        return os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    };

    // comparison operator ==
    bool operator==(const Point3& other) const {
        return x == other.x && y == other.y && z == other.z;
    };

    // comparison operator !=
    bool operator!=(const Point3& other) const {
        return !(*this == other);
    };
    
    // distance to another point
    T distanceTo(const Point3& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y) +
                         (z - other.z) * (z - other.z));
    };

    // normalize the point  
    Point3 normalize() const {
        T magnitude = std::sqrt(x * x + y * y + z * z);
        return Point3(x / magnitude, y / magnitude, z / magnitude);
    }

    // dot product with another point
    T dot(const Point3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // cross product with another point
    Point3 cross(const Point3& other) const {
        return Point3(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }
};

template<class T = double >
class Point2 {
    public:

    T x, y;

    // default constructor, Origin referance point
    Point2() : x(T(0)), y(T(0)) {}

    // main constructor 
    Point2(T x_, T y_) : x(x_), y(y_) {}

    // return the point as an Eigen vector
    Matrix<T, 2, 1> toEigenVector() const {
        return  Matrix<T, 2, 1>(x, y);
    }

    // create a Point2d from an Eigen vector
    static Point2 fromEigenVector(const Matrix<T, 2, 1>& vec) {
        return Point2(vec.x(), vec.y());
    }

    // addition
    Point2 operator+(const Point2& other) const {
        return Point2d(x + other.x, y + other.y);
    }

    // subtraction
    Point2 operator-(const Point2& other) const {
        return Point2(x - other.x, y - other.y);
    }

    // scalar multiplication
    Point2 operator*(T scalar) const {
        return Point2d(x * scalar, y * scalar);
    }

    // input operator
    friend std::istream& operator>>(std::istream& is, Point2& point) {
        return is >> point.x >> point.y;
    }

    // output operator
    friend std::ostream& operator<<(std::ostream& os, const Point2& point) {
        return os << "(" << point.x << ", " << point.y << ")";
    }

    // comparison operator ==
    bool operator==(const Point2& other) const {
        return x == other.x && y == other.y;
    }

    // comparison operator !=
    bool operator!=(const Point2& other) const {
        return !(*this == other);
    }

    // distance to another point
    T distanceTo(const Point2& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y));
    }

    // normalize the point  
    Point2 normalized() const {
        T magnitude = std::sqrt(x * x + y * y);
        return Point2(x / magnitude, y / magnitude);
    }

    // dot product with another point
    T dot(const Point2& other) const {
        return x * other.x + y * other.y;
    }
};

// this struct is used to reprsent a fixed point respect to time 
template<class T = double >
class Point4{
    public:

    T x, y, z, t;

    // default constructor
    Point4() : x(T(0)),y(T(0)),z(T(0)),t(T(0)){}

    // fixed point 
    Point4(T x_,T y_,T z_):x(x_),y(y_),z(z_), t(T(0)){}

    // full Constructor
    Point4(T x_,T y_,T z_,T t_):x(x_), y(y_),z(z_), t(t_) {}

    // return the point as an Eigen vector
    Matrix<T,4,1> toEigenVector() const {
        return Matrix<T,4,1>(x, y, z, t);
    }

    // create a Point4 from an Eigen vector
    static Point4 fromEigenVector(const Matrix<T,4,1>& vec) {
        return Point4(vec.x(), vec.y(), vec.z(), vec(3));
    }

    // addition
    Point4 operator+(const Point4& other) const {
        return Point4(x + other.x, y + other.y, z + other.z, t + other.t);
    }

    // subtraction
    Point4 operator-(const Point4& other) const {
        return Point4(x - other.x, y - other.y, z - other.z, t - other.t);
    }

    // scalar multiplication
    Point4 operator*(T scalar) const {
        return Point4(x*scalar,y*scalar,z*scalar,t*scalar);
    }

    // input operator
    friend std::istream& operator>>(std::istream& is, Point4& point) {
        return is >> point.x >> point.y >> point.z >> point.t;
    }

    // output operator
    friend std::ostream& operator<<(std::ostream& os, const Point4& point) {
        return os << "(" << point.x << ", " << point.y << ", " << point.z << ", " << point.t << ")";
    }

    // comparison operator ==
    bool operator==(const Point4& other) const {
        return x == other.x && y == other.y && z == other.z && t == other.t;
    }

    // comparison operator !=
    bool operator!=(const Point4& other) const {
        return !(*this == other);
    }

    // distance to another point
    T distanceTo(const Point4& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y) +
                         (z - other.z) * (z - other.z) +
                         (t - other.t) * (t - other.t));
    }

    // normalize the point  
    Point4 normalized() const {
        T magnitude = std::sqrt(x * x + y * y + z * z + t * t);
        return Point4(x / magnitude, y / magnitude, z / magnitude, t / magnitude);
    }

    // dot product with another point
    T dot(const Point4& other) const {
        return x * other.x + y * other.y + z * other.z + t * other.t;
    }
};

typedef Point2<double> Point2d;
typedef Point2<float>  Point2f;
typedef Point3<double> Point3d;
typedef Point3<float>  Point3f;
typedef Point4<double> Point4d;
typedef Point4<float>  Point4f;
}; // namsepace rpl


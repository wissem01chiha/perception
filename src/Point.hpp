#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>

namespace ptk {

template <typename T>
struct Point3 {

    glm::vec<3, T, glm::defaultp> data;

    // Default constructor
    Point3(T x_, T y_, T z_) : data(x_, y_, z_) {}

    // Constructor from glm::vec
    Point3(const glm::vec<3, T, glm::defaultp>& vec) : data(vec) {}

    // Return the point as a glm vector
    glm::vec<3, T, glm::defaultp> toGlmVector() const {
        return data;
    };

    // Create a Point3 from a glm vector
    static Point3 fromGlmVector(const glm::vec<3, T, glm::defaultp>& vec) {
        return Point3(vec);
    };

    // Addition
    Point3 operator+(const Point3& other) const {
        return Point3(data + other.data);
    };

    // Subtraction
    Point3 operator-(const Point3& other) const {
        return Point3(data - other.data);
    };

    // Scalar multiplication
    Point3 operator*(T scalar) const {
        return Point3(data * scalar);
    };

    // Input operator
    friend std::istream& operator>>(std::istream& is, Point3& point) {
        return is >> point.data.x >> point.data.y >> point.data.z;
    };

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Point3& point) {
        return os << "(" << point.data.x << ", " << point.data.y << ", " << point.data.z << ")";
    };

    // Comparison operator ==
    bool operator==(const Point3& other) const {
        return data == other.data;
    };

    // Comparison operator !=
    bool operator!=(const Point3& other) const {
        return !(*this == other);
    };

    // Distance to another point
    T distanceTo(const Point3& other) const {
        return glm::distance(data, other.data);
    };

    // Normalize the point  
    Point3 normalize() const {
        return Point3(glm::normalize(data));
    };

    // Dot product with another point
    T dot(const Point3& other) const {
        return glm::dot(data, other.data);
    };

    // Cross product with another point
    Point3 cross(const Point3& other) const {
        return Point3(glm::cross(data, other.data));
    };
};

template<typename T>
struct Point2 {
 
    glm::vec<2, T, glm::defaultp> data;

    // default constructor, Origin reference point
    Point2() : data(T(0), T(0)) {}

    // main constructor
    Point2(T x_, T y_) : data(x_, y_) {}

    // Constructor from glm::vec
    Point2(const glm::vec<2, T, glm::defaultp>& vec) : data(vec) {}

    // return the point as a glm vector
    glm::vec<2, T, glm::defaultp> toGlmVector() const {
        return data;
    }

    // create a Point2 from a glm vector
    static Point2 fromGlmVector(const glm::vec<2, T, glm::defaultp>& vec) {
        return Point2(vec);
    }

    // addition
    Point2 operator+(const Point2& other) const {
        return Point2(data + other.data);
    }

    // subtraction
    Point2 operator-(const Point2& other) const {
        return Point2(data - other.data);
    }

    // scalar multiplication
    Point2 operator*(T scalar) const {
        return Point2(data * scalar);
    }

    // input operator
    friend std::istream& operator>>(std::istream& is, Point2& point) {
        return is >> point.data.x >> point.data.y;
    }

    // output operator
    friend std::ostream& operator<<(std::ostream& os, const Point2& point) {
        return os << "(" << point.data.x << ", " << point.data.y << ")";
    }

    // comparison operator ==
    bool operator==(const Point2& other) const {
        return data == other.data;
    }

    // comparison operator !=
    bool operator!=(const Point2& other) const {
        return !(*this == other);
    }

    // distance to another point
    T distanceTo(const Point2& other) const {
        return glm::distance(data, other.data);
    }

    // normalize the point  
    Point2 normalized() const {
        return Point2(glm::normalize(data));
    }

    // dot product with another point
    T dot(const Point2& other) const {
        return glm::dot(data, other.data);
    }
};
typedef Point2<double> Point2d;
typedef Point2<float>  Point2f;
typedef Point3<double> Point3d;
typedef Point3<float>  Point3f;
}; // namsepace ptk


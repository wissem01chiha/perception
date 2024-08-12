#pragma once

#include <cmath>
#include <limits>
#include <complex>
#include <stdexcept>

#include <Eigen/Dense>

using namespace Eigen;

namespace rpl
{
/**
 * @brief Template Base class for all possible 2D rotations in SO(2)
 */
template<class Precision = double>
class SO2
{ 
public:

    // Default constructor
    SO2() : angle(Precision(0)) {}

    // Construct from a complex number (complex exponential)
    SO2(const std::complex<Precision>& z) {
        angle = std::arg(z);  // Extract angle from complex number
    }

    // Construct from a given matrix
    SO2(const Matrix<Precision, 2, 2>& Mat2) {
        if (!isSO2(Mat2)) {
            throw std::invalid_argument("Matrix is not a valid SO(2) element.");
        }
        angle = std::atan2(Mat2(1, 0), Mat2(0, 0));
    }

    // Construct from a given 2D eigen quaternion (for SO(2), it's essentially a 2D rotation)
    SO2(const Quaternion<Precision>& q) {
        if (q.w() < 0) {
            throw std::invalid_argument("Quaternion must be normalized and represent a valid rotation.");
        }
        angle = 2 * std::atan2(q.z(), q.w());
    }

    // Construct from two 2D vectors
    SO2(const Vector2<Precision>& v1, const Vector2<Precision>& v2) {
        Precision dot = v1.dot(v2);
        Precision det = v1.x() * v2.y() - v1.y() * v2.x();
        angle = std::atan2(det, dot);
    }

    // Return the identity SO2 element (rotation by 0 degrees)
    static SO2 identity() {
        return SO2();
    }

    // Multiply two SO2 elements
    SO2 operator*(const SO2<Precision>& other) const {
        return SO2(angle + other.angle);
    }

    // Get the inverse of the SO2 element
    SO2 inverse() const {
        return SO2(-angle);
    }

    // Return a random SO2 element (random angle)
    static SO2 random() {
        Precision rand_angle = static_cast<Precision>(2 * M_PI * 
        (rand() / static_cast<Precision>(RAND_MAX)));
        return SO2(rand_angle);
    }

    // Check if a given matrix is an element in SO2
    static bool isSO2(const Matrix<Precision, 2, 2>& Mat2) {
        Matrix<Precision, 2, 2> I = Matrix<Precision, 2, 2>::Identity();
        return Mat2.transpose() * Mat2.isApprox(I) && std::abs(Mat2.determinant() - 1.0) < 1e-6;
    }

    // Get the matrix form of the SO2 element
    Matrix<Precision, 2, 2> toEigenMatrix() const {
        Matrix<Precision, 2, 2> mat;
        mat << std::cos(angle), -std::sin(angle),
               std::sin(angle),  std::cos(angle);
        return mat;
    }

    // Return the complex representation
    std::complex<Precision> toComplex() const {
        return std::complex<Precision>(std::cos(angle), std::sin(angle));
    }

private:
    Precision angle;  // Rotation angle in radians
};
} // namespace rpl
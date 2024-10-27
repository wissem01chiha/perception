#pragma once

#include <cmath>
#include <complex>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ptk {
    
template <typename T>
struct SO2 {

    T angle;

    // Default constructor
    SO2() : angle(T(0)) {}

    // Constructor with specific angle value in radians
    SO2(T angle_) : angle(angle_) {}

    // Construct from a complex number (complex exponential)
    SO2(const std::complex<T>& z) {
        if (std::abs(z) == 0) {
            throw std::invalid_argument("Complex number cannot be zero.");
        }
        angle = std::arg(z);
    }
    
    // Construct from a given 2x2 matrix
    SO2(const glm::tmat2x2<T>& mat2) {
        if (!isSO2(mat2)) {
            throw std::invalid_argument("Matrix is not a valid SO(2) element.");
        }
        angle = std::atan2(mat2[1][0], mat2[0][0]);
    }

    // Construct from a given 2D quaternion
    SO2(const glm::qua<T, glm::packed_highp>& q) {
        if (q.w < 0) {
            throw std::invalid_argument("Quaternion must represent a valid rotation.");
        }
        angle = 2 * std::atan2(q.z, q.w);
    }

    // Construct from two 2D vectors
    SO2(const glm::tvec2<T>& v1, const glm::tvec2<T>& v2) {
        T dot = glm::dot(v1, v2);
        T det = v1.x * v2.y - v1.y * v2.x;
        angle = std::atan2(det, dot);
    }

    // Return the identity SO2 element (rotation by 0 degrees)
    static SO2<T> identity() {
        return SO2<T>(0);
    }

    // Get the inverse of the SO2 element
    SO2<T> inverse() const {
        return SO2<T>(-angle);
    }

    // Check if a given matrix is an element in SO2
    static bool isSO2(const glm::tmat2x2<T>& mat2) {
        glm::tmat2x2<T> I(1.0);
        const T epsilon = T(1e-6);
        glm::tmat2x2<T> product = glm::transpose(mat2) * mat2;
        bool isOrthogonal = true;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (std::abs(product[i][j] - I[i][j]) > epsilon) {
                    isOrthogonal = false;
                    break;
                }
            }
            if (!isOrthogonal) break;
        }
        bool isDeterminantOne = std::abs(glm::determinant(mat2) - 1.0) < epsilon;
        return isOrthogonal && isDeterminantOne;
    }

    // Multiply two SO2 elements
    SO2<T> operator*(const SO2<T>& other) const {
        return SO2<T>(angle + other.angle);
    }

    // Return a random SO2 element (random angle)
    static SO2<T> random() {
        T rand_angle = 2 * glm::pi<T>() * (rand() / static_cast<T>(RAND_MAX));
        return SO2<T>(rand_angle);
    }

    // Get the matrix form of the SO2 element
    glm::tmat2x2<T> toGLMMatrix() const {
        glm::tmat2x2<T> mat;
        mat[0][0] = std::cos(angle);
        mat[0][1] = -std::sin(angle);
        mat[1][0] = std::sin(angle);
        mat[1][1] = std::cos(angle);
        return mat;
    }

    // Return the complex representation
    std::complex<T> toComplex() const {
        return std::complex<T>(std::cos(angle), std::sin(angle));
    }
};
typedef SO2<double> SO2d;
typedef SO2<float> SO2f;
}; // namespace ptk

#pragma once

#include <cmath>
#include <complex>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <Eigen/Dense>

using namespace Eigen;

namespace ptk {

template<typename T>
struct SE3 {

    Matrix<T, 4, 4> Mat;
    glm::mat<4,4,T> Mat_;

    // Default constructor - Identity Rotation-unit-Translation
    SE3() : Mat(Matrix<T, 4, 4>::Identity()) {}

    // Checks if a matrix is a valid SE3 rotation matrix.
    static bool isSE3(const Matrix<T, 4, 4>& mat) {
        Matrix<T, 1, 4> bottomRow = mat.row(3);
        if (!bottomRow.isApprox(Matrix<T, 1, 4>(0, 0, 0, 1))) {
            return false;
        }
        Matrix<T, 3, 3> rotation = mat.template block<3, 3>(0, 0);
        Matrix<T, 3, 3> shouldBeIdentity = rotation * rotation.transpose();
        if (!shouldBeIdentity.isApprox(Matrix<T, 3, 3>::Identity())) {
            return false;
        }
        if (std::abs(rotation.determinant() - 1.0) > 1e-6) {
            return false;
        }
        return true;
    };

    // Construct from the full homogeneous matrix 
    SE3(const Matrix<T, 4, 4>& Mat4) {
        if (!isSE3(Mat4)) {
            throw std::invalid_argument("Input matrix is not a valid rotation matrix in SE(3).");
        } else {
            Mat = Mat4;
        }
    };

    // Construct from the rotation matrix and a translation vector 
    SE3(const Matrix<T, 3, 3>& R, const Matrix<T, 3, 1>& T) {
        if (!isSE3((Matrix<T, 4, 4>() << R, T, Matrix<T, 1, 3>::Zero(), 1.0).finished())) {
            throw std::invalid_argument("Input matrix is not a valid rotation matrix in SE(3).");
        } else {
            Mat.template block<3, 3>(0, 0) = R;
            Mat.template block<3, 1>(0, 3) = T;
            Mat.template block<1, 3>(3, 0) = Matrix<T, 1, 3>::Zero();
            Mat(3, 3) = 1.0;
        }
    };

    static SE3 identity() {
        return SE3();
    };

    // Multiply two SE3 elements
    SE3 operator*(const SE3<T>& other) const {
        return SE3(Mat * other.Mat);
    };

    // Add two SE3 elements
    SE3 operator+(const SE3<T>& other) const {
        Matrix<T, 3, 1> T1 = Mat.template block<3, 1>(0, 3);
        Matrix<T, 3, 1> T2 = other.Mat.template block<3, 1>(0, 3);
        return SE3(Mat.template block<3, 3>(0, 0), T1 + T2);
    };

    // Subtract two SE3 elements
    SE3 operator-(const SE3<T>& other) const {
        Matrix<T, 3, 1> T1 = Mat.template block<3, 1>(0, 3);
        Matrix<T, 3, 1> T2 = other.Mat.template block<3, 1>(0, 3);
        return SE3(Mat.template block<3, 3>(0, 0), T1 - T2);
    };

    // Check if the element is a pure rotation
    bool isRotation() const {
        return Mat.template block<3, 1>(0, 3).isZero();
    };

    // Check if the element is a pure translation
    bool isTranslation() const {
        return Mat.template block<3, 3>(0, 0).isIdentity();
    };
}; 
typedef SE3<double> SE3d;
typedef SE3<float> SE3f;
}; // namespace ptk
#pragma once

#include <cmath>
#include <limits>
#include <stdexcept>
#include <Eigen/Dense>

using namespace Eigen;

namespace rpl {

/**
 * @brief Represents an element of SO(3) - rotation in 3D.
 * SO(3) is the group of rotations in 3D. By default, an element of SO3
 * is represented as a quaternion.
 */
template <class Precision = double>
class SO3 {
public:
    // Default constructor - Identity Quaternion
    SO3() : x_(0), y_(0), z_(0), w_(1) {}

    // Constructor from Quaternion
    SO3(const Precision& x, const Precision& y, const Precision& z, const Precision& w)
        : x_(x), y_(y), z_(z), w_(w) {}

    /**
     * @brief Constructs SO3 from axis-angle representation.
     * @param direction The rotation axis.
     * @param angle The rotation angle in radians.
     * @return A SO3 object representing the rotation.
     */
    SO3 FromAxisAngle(const Vector3<Precision>& direction, Precision angle) const {
        Precision norm = direction.norm();
        if (norm <= std::numeric_limits<Precision>::epsilon()) {
            return SO3();
        }
        angle *= 0.5;
        Precision s = sin(angle) / norm;
        return SO3(direction.x() * s, direction.y() * s, direction.z() * s, cos(angle));
    }

    /**
     * @brief Constructs SO3 from pitch, yaw, and roll angles.
     * @param pitch The pitch angle.
     * @param yaw The yaw angle.
     * @param roll The roll angle.
     * @return A SO3 object representing the rotation.
     */
    static SO3 FromPitchYawRoll(const Precision& pitch, const Precision& yaw, const Precision& roll) {
        Precision halfAngle = M_PI / 360.0;
        Precision p = pitch * halfAngle;
        Precision y = yaw * halfAngle;
        Precision r = roll * halfAngle;

        Precision sr = sin(r);
        Precision cr = cos(r);
        Precision sp = sin(p);
        Precision cp = cos(p);
        Precision sy = sin(y);
        Precision cy = cos(y);

        Precision rx = sr * cp * cy - cr * sp * sy;
        Precision ry = cr * sp * cy + sr * cp * sy;
        Precision rz = cr * cp * sy - sr * sp * cy;
        Precision rw = cr * cp * cy + sr * sp * sy;

        return SO3(rx, ry, rz, rw);
    }

    /**
     * @brief Converts SO3 to axis-angle representation.
     * @return A vector containing the axis and angle.
     */
    Vector4<Precision> ToAxisAngle() const {
        if (w_ == 1 || w_ == -1) {
            Precision angle = Precision(0);
            Vector3<Precision> axis = Vector3<Precision>::Random().normalized();
            return Vector4<Precision>(axis.x(), axis.y(), axis.z(), angle);
        }

        Precision angle = 2 * acos(w_);
        Precision norm = sqrt(1 - w_ * w_);
        Precision xAxis = x_ / norm;
        Precision yAxis = y_ / norm;
        Precision zAxis = z_ / norm;

        return Vector4<Precision>(xAxis, yAxis, zAxis, angle);
    }

    /**
     * @brief Multiplies two SO3 elements.
     * @param other The other SO3 element.
     * @return The product of the two SO3 elements.
     */
    SO3 operator*(const SO3<Precision>& other) const {
        return SO3(
            w_ * other.x_ + x_ * other.w_ + y_ * other.z_ - z_ * other.y_,
            w_ * other.y_ + y_ * other.w_ + z_ * other.x_ - x_ * other.z_,
            w_ * other.z_ + z_ * other.w_ + x_ * other.y_ - y_ * other.x_,
            w_ * other.w_ - x_ * other.x_ - y_ * other.y_ - z_ * other.z_
        );
    }

    /**
     * @brief Checks if a matrix is a valid SO3 rotation matrix.
     * @param mat The matrix to check.
     * @return True if the matrix is a valid SO3 matrix, false otherwise.
     */
    static bool IsSO3(const Matrix<Precision, 3, 3>& mat) {
        Matrix<Precision, 3, 3> identity = Matrix<Precision, 3, 3>::Identity();
        bool isOrthogonal = (mat * mat.transpose() - identity).norm() < 1e-6;
        Precision det = mat.determinant();
        bool hasUnitDeterminant = std::abs(det - 1.0) < 1e-6;
        return isOrthogonal && hasUnitDeterminant;
    }

    /**
     * @brief Constructs SO3 from a rotation matrix.
     * @param mat The rotation matrix.
     * @return A SO3 object representing the rotation.
     * @throws std::invalid_argument If the matrix is not a valid rotation matrix.
     */
    static SO3 FromMatrix(const Matrix<Precision, 3, 3>& mat) {
        if (!IsSO3(mat)) {
            throw std::invalid_argument("Input matrix is not a valid rotation matrix in SO(3).");
        }

        Precision tr = mat.trace();
        Precision S;
        if (tr > 0) {
            S = sqrt(tr + 1.0) * 2.0;
            return SO3(
                (mat(2, 1) - mat(1, 2)) / S,
                (mat(0, 2) - mat(2, 0)) / S,
                (mat(1, 0) - mat(0, 1)) / S,
                0.25 * S
            );
        } else if ((mat(0, 0) > mat(1, 1)) && (mat(0, 0) > mat(2, 2))) {
            S = sqrt(1.0 + mat(0, 0) - mat(1, 1) - mat(2, 2)) * 2.0;
            return SO3(
                0.25 * S,
                (mat(0, 1) + mat(1, 0)) / S,
                (mat(0, 2) + mat(2, 0)) / S,
                (mat(2, 1) - mat(1, 2)) / S
            );
        } else if (mat(1, 1) > mat(2, 2)) {
            S = sqrt(1.0 + mat(1, 1) - mat(0, 0) - mat(2, 2)) * 2.0;
            return SO3(
                (mat(0, 1) + mat(1, 0)) / S,
                0.25 * S,
                (mat(1, 2) + mat(2, 1)) / S,
                (mat(0, 2) - mat(2, 0)) / S
            );
        } else {
            S = sqrt(1.0 + mat(2, 2) - mat(0, 0) - mat(1, 1)) * 2.0;
            return SO3(
                (mat(0, 2) + mat(2, 0)) / S,
                (mat(1, 2) + mat(2, 1)) / S,
                0.25 * S,
                (mat(1, 0) - mat(0, 1)) / S
            );
        }
    }

    /**
     * @brief Normalizes the quaternion.
     */
    void Normalize() {
        Precision norm2 = w_ * w_ + x_ * x_ + y_ * y_ + z_ * z_;
        if (norm2 != Precision(0) && std::fabs(norm2 - Precision(1)) > 
            std::numeric_limits<Precision>::epsilon()) {
            Precision magnitude = 1.0 / sqrt(norm2);
            w_ *= magnitude;
            x_ *= magnitude;
            y_ *= magnitude;
            z_ *= magnitude;
        }
    }

private:
    Precision x_;
    Precision y_;
    Precision z_;
    Precision w_;
};

using SO3d = SO3<double>;
using SO3f = SO3<float>;
using SO3i = SO3<int>;
using SO3i32 = SO3<int32_t>;
using SO3i64 = SO3<int64_t>;

} // namespace rpl
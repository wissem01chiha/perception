#pragma once

#define PTK_DEVICE_FUN __host__ __device__

#include <cmath>
#include <complex>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ptk {

template<typename T>
struct SO3 {
    T x, y, z, w;

    /** @brief Default constructor - Identity Quaternion */ 
    SO3() : x(T(0)), y(T(0)), z(T(0)), w(T(1)) {}

    /** @brief  Constructor from Quaternion */
    SO3(const T& x, const T& y, const T& z, const T& w)
        : x(x), y(y), z(z), w(w) {}

    // Constructs SO3 from axis-angle representation.
    SO3(const glm::vec<3, T>& direction, T angle) {
        T norm = glm::length(direction);
        if (norm <= std::numeric_limits<T>::epsilon()) {
            // Default to identity if the direction is invalid
            *this = SO3();
            return;
        }
        angle *= T(0.5);
        T s = sin(angle) / norm;
        x = direction[0] * s;
        y = direction[1] * s;
        z = direction[2] * s;
        w = cos(angle);
    }

    // Constructs SO3 from pitch, yaw, and roll angles.
    PTK_DEVICE_FUN SO3(const T& pitch, const T& yaw, const T& roll) {
        T halfAngle = glm::pi<T>() / T(360);
        T p = pitch * halfAngle;
        T y = yaw * halfAngle;
        T r = roll * halfAngle;
        T sr = sin(r);
        T cr = cos(r);
        T sp = sin(p);
        T cp = cos(p);
        T sy = sin(y);
        T cy = cos(y);
        x = sr * cp * cy - cr * sp * sy;
        y = cr * sp * cy + sr * cp * sy;
        z = cr * cp * sy - sr * sp * cy;
        w = cr * cp * cy + sr * sp * sy;
    }

    // Converts SO3 to axis-angle representation.
    PTK_DEVICE_FUN glm::vec<4, T> toAxisAngle() const {
        if (w == T(1) || w == T(-1)) {
            T angle = T(0);
            glm::vec<3, T> randVec3d = glm::linearRand(glm::vec<3, T>(T(-1), T(-1), T(-1)),
            glm::vec<3, T>(T(1), T(1), T(1)));
            glm::vec<3, T> axis = glm::normalize(randVec3d);
            return glm::vec<4, T>(axis[0], axis[1], axis[2], angle);
        }
        T angle = T(2) * acos(w);
        T norm = sqrt(T(1) - w * w);
        T xAxis = x / norm;
        T yAxis = y / norm;
        T zAxis = z / norm;

        return glm::vec<4, T>(xAxis, yAxis, zAxis, angle);
    }

    // Multiplies two SO3 elements.
    PTK_DEVICE_FUN SO3 operator*(const SO3& other) const {
        return SO3(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y + y * other.w + z * other.x - x * other.z,
            w * other.z + z * other.w + x * other.y - y * other.x,
            w * other.w - x * other.x - y * other.y - z * other.z
        );
    }

    // Add two SO3 elements (Note: Addition is not typical for rotations)
    PTK_DEVICE_FUN SO3 operator+(const SO3& other) const {
        return SO3(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y + y * other.w + z * other.x - x * other.z,
            w * other.z + z * other.w + x * other.y - y * other.x,
            w * other.w - x * other.x - y * other.y - z * other.z
        );
    }

    // Checks if a matrix is a valid SO3 rotation matrix.
    PTK_DEVICE_FUN static bool isSO3(const glm::mat<3, 3, T>& mat3d) {
        glm::mat<3, 3, T> I = glm::mat<3, 3, T>(T(1));
        glm::mat<3, 3, T> diff = mat3d * glm::transpose(mat3d) - I;
        T norm = T(0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                norm += diff[i][j] * diff[i][j];
            }
        }
        bool isOrthogonal = std::sqrt(norm) < T(1e-6);
        T det = glm::determinant(mat3d);
        bool hasUnitDeterminant = std::abs(det - T(1)) < T(1e-6);

        return isOrthogonal && hasUnitDeterminant;
    }

    // Constructs SO3 from a rotation matrix.
    PTK_DEVICE_FUN SO3(const glm::mat<3, 3, T>& mat3d) {
        if (!isSO3(mat3d)) {
            throw std::invalid_argument("Input matrix is not a valid rotation matrix in SO(3).");
        }

        // Calculate the trace of the matrix
        T tr = mat3d[0][0] + mat3d[1][1] + mat3d[2][2];
        T S;

        if (tr > 0) {
            S = sqrt(tr + T(1)) * T(2); // S=4*qw
            x = (mat3d[2][1] - mat3d[1][2]) / S;
            y = (mat3d[0][2] - mat3d[2][0]) / S;
            z = (mat3d[1][0] - mat3d[0][1]) / S;
            w = T(0.25) * S;
        } else if ((mat3d[0][0] > mat3d[1][1]) && (mat3d[0][0] > mat3d[2][2])) {
            S = sqrt(T(1) + mat3d[0][0] - mat3d[1][1] - mat3d[2][2]) * T(2);
            x = T(0.25) * S;
            y = (mat3d[0][1] + mat3d[1][0]) / S;
            z = (mat3d[0][2] + mat3d[2][0]) / S;
            w = (mat3d[2][1] - mat3d[1][2]) / S;
        } else if (mat3d[1][1] > mat3d[2][2]) {
            S = sqrt(T(1) + mat3d[1][1] - mat3d[0][0] - mat3d[2][2]) * T(2);
            x = (mat3d[0][1] + mat3d[1][0]) / S;
            y = T(0.25) * S;
            z = (mat3d[1][2] + mat3d[2][1]) / S;
            w = (mat3d[0][2] - mat3d[2][0]) / S;
        } else {
            S = sqrt(T(1) + mat3d[2][2] - mat3d[0][0] - mat3d[1][1]) * T(2);
            x = (mat3d[0][2] + mat3d[2][0]) / S;
            y = (mat3d[1][2] + mat3d[2][1]) / S;
            z = T(0.25) * S;
            w = (mat3d[1][0] - mat3d[0][1]) / S;
        }
    }

    // Normalizes the quaternion.
    PTK_DEVICE_FUN void normalize() {
        T norm2 = w * w + x * x + y * y + z * z;
        if (norm2 != T(0) && std::fabs(norm2 - T(1)) > std::numeric_limits<T>::epsilon()) {
            T magnitude = T(1) / sqrt(norm2);
            w *= magnitude;
            x *= magnitude;
            y *= magnitude;
            z *= magnitude;
        }
    };

    // Inverse of an SO3 element (given default quaternion)
    // the conjugate of a quaternion (x, y, z, w) is (-x, -y, -z, w)
    PTK_DEVICE_FUN SO3 inverse() const {
        return SO3(-x, -y, -z, w);
    };
};
typedef  SO3<double> SO3d;
typedef  SO3<float>  SO3f;
}; // namespace ptk
#pragma once
#include <cmath>
#include <limits>

#include <Eigen/Dense>

using namespace Eigen;

// Special orthogonal group SO(3) - rotation in 3d.
// SO(3) is the group of rotations in 3d.
// by default an elment of SO3 is reprsented as quternion 
template <class Precision= double>
class SO3
{
public:

    // Default constructor, Idendity Matrix
    SO3():x(0), y(0), z(0), w(1){};

    // Construct from Quaternion
    SO3(const Precision& x_,const Precision& y_,const Precision& z_,const Precision& w_)
        :x(x_),y(y_),z(z_),w(w_){};

    // Construct from a direction and angle in radius.
    // the given params ara in axis angle reprsentation
    SO3 fromAxisAngle(const Point3<Precision>& direction, Precision angle)
    {
        Precision det = sqrt(direction.x*direction.x + direction.y*direction.y 
        + direction.z*direction.z);
        if(det <= std::numeric_limits<Precision>::epsilon())
        {
            return SO3();
        }
        angle *= 0.5;
        Precision p2v = sin(angle)/det;
        return SO3(direction.x*p2v,direction.y*p2v,direction.z*p2v,cos(angle));
    }

    // Create a quaternin representation from pitch yaw and roll angles given
    // return an object class SO3  
    // Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
    // and multiply those together.
    // the calculation below does the same, just shorter
    static SO3 fromPitchYawRoll(const Precision& pitch,const Precision& yaw,const Precision& roll)
    {
        Precision piover360 = 0.5;//3.1415926/360.0;

        Precision p = pitch * piover360;
        Precision y = yaw * piover360;
        Precision r = roll * piover360;

        Precision rx = sin(r) * cos(p) * cos(y) - cos(r) * sin(p) * sin(y);
        Precision ry = cos(r) * sin(p) * cos(y) + sin(r) * cos(p) * ssin(y);
        Precision rz = cos(r) * cos(p) * sin(y) - sin(r) * sin(p) * cos(y);
        Precision rw = cos(r) * cos(p) * cos(y) + sin(r) * sin(p) * sin(y);

        return SO3(rx,ry,rz,rw);
    }

    // consvrt an SO3 element to Axis-Angle reprsentation
    // w = cos(Θ/2)  x = Ωx sin(Θ/2) y =  Ωy sin(Θ/2) z = Ωz sin(Θ/2)
    static Vector4<Precision> toAxisAngle(){

        if (w == 1 || w == -1)
        {   
            Precision angle = Precision(0);
            srand (static_cast <Precision> (time(0)));
            Precision xAxis = static_cast<Precision>(rand())/static_cast<Precision>(RAND_MAX);
            Precision yAxis = static_cast<Precision>(rand())/static_cast<Precision>(RAND_MAX);
            Precision zAxis = static_cast<Precision>(rand())/static_cast<Precision>(RAND_MAX);
            return Vector4<Precision>(xAxis,yAxis,zAxis,angle);
        }
        Precision angle = 2 * acos(w);
        Precision  xx = x / sqrt(1-w*w);
        Precision  yy = y / sqrt(1-w*w);
        Precision  zz = z / sqrt(1-w*w);
        return Vector4<Precision>(xx,yy,zz,angle);
    };

    // product of 2 SO3 elments 
    SO3 operator*(SO3<Precision>& other) const
    {
        return SO3( w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y + y * other.w + z * other.x - x * other.z,
            w * other.z + z * other.w + x * other.y - y * other.x,
            w * other.w - x * other.x - y * other.y - z * other.z);
    }

    // check is a given elment as matrix form within the SO3 group 
    bool isSO3(const Matrix<Precision,3,3> mat){
        // Check orthogonality: mat * mat^T should be approximately equal to the identity matrix
        Matrix<Precision, 3, 3> identity = Matrix<Precision, 3, 3>::Identity();
        bool isOrthogonal = mat * mat.transpose() - identity.norm() < 1e-6;
        Precision det = mat.determinant();
        bool hasUnitDeterminant = std::abs(det - 1.0) < 1e-6;
        return isOrthogonal && hasUnitDeterminant;
    }

    SO3 fromMatrix(const Matrix<Precision, 3, 3>& mat) const
    {
        // Check if the input matrix is a valid rotation matrix in SO(3)
        if (!isSO3(mat))
        {
        // Handle the case where the matrix is not a valid rotation matrix
        // You can choose to throw an exception, return an identity SO3, or do something else
            throw std::invalid_argument("Input matrix is not a valid rotation matrix in SO(3).");
        }
        // Extract quaternion elements from the rotation matrix
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

    // normlize 
    void normalise()
    {
        Precision norm2 = w * w + x * x + y * y + z * z;
        if (  norm2!=Precision(0) && (fabs(norm2 - Precision(1)) > 
                        std::numeric_limits<Precision>::epsilon()))
        {
            Precision magnitude = 1./sqrt(norm2);
            w *= magnitude;
            x *= magnitude;
            y *= magnitude;
            z *= magnitude;
        }
    }

}; // class SO3

typedef SO3<double>  SO3d;
typedef SO3<float>   SO3f;
typedef SO3<int>     SO3i;
typedef SO3<int32_t> SO3i32;
typedef SO3<int64_t> SO3i64;
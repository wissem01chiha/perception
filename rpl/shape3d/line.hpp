#pragma once
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

namespace rpl {  
// base class for projective lines representation
//  a projective lines defined by the equation:
// u1 x + u2 y+ u3 z =0 where u1 u2 u3 not all == 0
//
template<class Precision = double >
class Line {

    public:
    Precision u1, u2 , u3;

    // Default Construtor
    Line(Precision& u1_, Precision& u2_, Precision& u3_ ):u1(u1_),u2(u2_),u3(u3_){};
    // constrict a line from projective point duality line-point

    Matrix<Precision, 3, 1> toEigenVector() const{
        return Vector3<Precision>(u1, u2, u3);
    }
    // modeling the lines uncertailty
    
    private:

        bool validateInput(){
        
        }
 
};
}; // namespace rpl 
 
#pragma once
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

// base class for projective lines representation
//  a projective lin eis defined by the equation:
// u1x+u2y+u3z =0 where u1 u2 u3 not all ==0
template<class Precision = double >
class Line
{
public:

    Precision u1, u2 , u3;
    // Default Construtor
    Line(Precision& u1_, Precision& u2_, Precision& u3_ ):u1(u1_),u2(u2_),u3(u3_){};
    // constrict a line from projective point duality line-point


    // modeling the lines uncertailty 

 
};

 
#pragma once
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "PointXd.hpp"
using namespace Eigen;


namespace geometry
{

template<typename T>
struct Box2d
{
    Point2d<T> Pt1, Pt2, Pt3, Pt4;

    // Constructor 
    Box2d(Point2d<T> Pt1_,Point2d<T> Pt2_,Point2d<T> Pt3_,Point2d<T> Pt4_):
    Pt1(Pt1_), Pt2(Pt2_), Pt2(Pt2_), Pt3(Pt3_),Pt4(Pt4_){};

    // Return the box as an Eigen matrix representation 
    Matrix<T, 2, 4> toEigenMatrix() const {

    }
    
    // 
    rotation(){

    }

    // check if the box represent a rectagle
    bool is_rectangular(){

    }

};

    
    
} // namespace geometry

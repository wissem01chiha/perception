#pragma once
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "PointXd.hpp"

using namespace Eigen;

namespace geometry {

template<typename T>
struct Line2d
{
    Point2d<T> Pt1, Pt2;

    // Constructor
    Line2d(Point2d<T> Pt1_, Point2d<T> Pt2_):Pt1(Pt1_), Pt2(Pt2_){};

    // Return the line as an Eigen vector 
    Matrix<T, 2, 1> toEigenVector() const {
        return Matrix<T,2,1>(Pt1.x-Pt2.x,Pt1.y-Pt2.y);
    }

    // Create a Line2d from an Eigen vector
    static Line2d fromEigenVector(const Matrix<T, 2, 1>& vec){
        return Point3d(vec.x(), vec.y(), vec.z());
    }

    // Addition 
    Line2d operator+(const Line2d& other) const{

    }

    // Soustraction
    Line2d<T>  operator-(const Line2d& other)const {
        
    }
    
    // Cross product with an other line 
    Line2d cross(const Line2d& other ){

    }

    // Input 
};

template<typename T>
struct Line3d
{
    Point3d<T> Pt1, Pt2;

    // Constructor 
    Line3d(Point3d Pt1_, Point3d Pt2_):Pt1(Pt1_),Pt2(Pt2_){};

    // Return the line as an Eigen vector  
    Matrix<T, 3, 1> toEigenVector() const {
        return Matrix<T, 3, 1>(Pt1.x - Pt2.x, Pt1.y - Pt2.y);
    }

    // 

};

template<typename T>
struct Line4d
{
    Point4d<T> Pt1, Pt2;

    // Constructor 
    
};


} // namespace geometry
#pragma once

#include <Eigen/Core>
#include <Eigen/Dense>

// Estimate the fundamental matrix from two image point 
// correspondences 
// Inputs:
//     x1 - size (N x 2) matrix of points in image 1
//     x2 - size (N x 2) matrix of points in image 2, 
//     each row corresponding to x1
// Output:
//    F - size (3 x 3) fundamental matrix with rank 2
void estimateFundamentalMatrix(const Eigen::MatrixXd x1,
                             const Eigen::MatrixXd x2, 
                             Eigen::Matrix3d& F){

};

// EstimateLinearPnP
// solve the epiplor problem 
void estimateLinearPnP(){

}

// solve the traingl
void nonlinearTriangulation();


//
void essentialMatrixFromFundamentalMatrix();

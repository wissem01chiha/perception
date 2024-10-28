#pragma once 

#include <vector> 

#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp> 

#include <Eigen/Core>
#include <Eigen/Dense>

#include "math.h"
#include "utils.h"

//
//
void extractCamera3DPose(const Eigen::Matrix3d E){

    Eigen::MatrixXd W;
    W << 0, -1, 0,
        1,  0, 0,
        0,  0, 1;

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(E, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Eigen::MatrixXd U = svd.U();  
    Eigen::VectorXd S = svd.singularValues(); 
    Eigen::MatrixXd V = svd.v();  

    Eigen::MatrixXd R = U * W * V.transpose();
    std::vector<Eigen::MatrixXd> Rset(4);
    std::vector<Eigen::MatrixXd> Cset(4);

    auto calculateRAndC = [&](const Eigen::MatrixXd& R, const Eigen::MatrixXd& C, int index) {
        if (R.determinant() < 0) {
            Rset[index] = -R;
            Cset[index] = -C;
        } else {
            Rset[index] = R;
            Cset[index] = -R.transpose() * C;
        }
    };

    // First set of calculations
    Eigen::VectorXd C = U.col(2);
    calculateRAndC(U * W * V.transpose(), C, 0);

    // Second set of calculations
    C = -U.col(2);
    calculateRAndC(U * W * V.transpose(), C, 1);

    // Third set of calculations
    C = U.col(2);
    calculateRAndC(U * W.transpose() * V.transpose(), C, 2);

    // Fourth set of calculations
    C = -U.col(2);
    calculateRAndC(U * W.transpose() * V.transpose(), C, 3);

    // Output the results
    for (int i = 0; i < 4; ++i) {
        std::cout << "Rset[" << i << "]:\n" << Rset[i] << "\n";
        std::cout << "Cset[" << i << "]:\n" << Cset[i] << "\n";
    }
}

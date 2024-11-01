

// https://graphics.stanford.edu/~jgao/collision-detection.html


template <typename T>
void Camera<T>::compute3DPose(const Eigen::Matrix3<T> E)
{
	Eigen::MatrixXd W;
    W << 0, -1, 0,
        1,  0, 0,
        0,  0, 1;

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(E, Eigen::ComputeThinU 
                                          | Eigen::ComputeThinV);
    Eigen::MatrixXd U = svd.matrixU();  
    Eigen::VectorXd S = svd.singularValues(); 
    Eigen::MatrixXd V = svd.matrixV();  

    Eigen::MatrixXd R = U * W * V.transpose();
    std::vector<Eigen::MatrixXd> Rset(4);
    std::vector<Eigen::MatrixXd> Cset(4);

    auto calculateRAndC = [&](const Eigen::MatrixXd& R, 
                              const Eigen::MatrixXd& C, int index) {
        if (R.determinant() < 0) {
            Rset[index] = -R;
            Cset[index] = -C;
        } else {
            Rset[index] = R;
            Cset[index] = -R.transpose() * C;
        }
    };

    Eigen::VectorXd C = U.col(2);
    calculateRAndC(U * W * V.transpose(), C, 0);
    C = -U.col(2);
    calculateRAndC(U * W * V.transpose(), C, 1);
    C = U.col(2);
    calculateRAndC(U * W.transpose() * V.transpose(), C, 2);
    C = -U.col(2);
    calculateRAndC(U * W.transpose() * V.transpose(), C, 3);
}
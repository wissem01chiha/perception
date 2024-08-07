#pragma once
#include<cmath>

#include <Eigen/Dense>
#include "../geometry/point.hpp"

using namespace Eigen;

namespace rpl {
// base class for modeling the carmera and calbiration function utils
// this is camera class used as a ref to all carmera modesl as interface 
// ref: https://ftp.cs.toronto.edu/pub/psala/VM/camera-parameters.pdf
//https://www.oreilly.com/library/view/programming-computer-vision/9781449341916/ch04.html
template<class Precision = double , size_t Resolution, size_t fps>
class Camera{
    public:

    // Default Constructor 
    Camera();

    // given a point in world frame computes its coordianates in image frame x y
    // 
    Point2<Precision> world2image(const Point3<Precision>& pt3){

    };

    // given a point in image frame (retinal ) it computes in the world frmae (estimation)
    Point3<Precision> image2world(const Point2<Precision>& pt2){

    };

    // estimate the camera intrins paramters R and T from N sampled image points
    // (xi, yi) in the image frame and their correspending (Xi, Yi, Zi ) in the world frame
    void computeCameraModel(){ 

    };

    // get the camera aspec ratio
    Precision getAspectRatio(){
        return aspectRatio;
    }

    //
    void computeCenter(){

    };



private:
    // camera intrinsp paramters 
    Matrix<Precision, 3, 3> R;           // rotation matrix 
    Matrix<Precision, 3, 1> T;           // h matrix 
    Precision               aspectRatio; // sy/sx 
    Precision               k1;          // radial distoration coefficent
    Precision               fx;          // length in effective horizontal pixel size, focal length  
    Point2<Precision>       center ;     // image center coordiantes 

    bool validateInput(){

    };
}; // class Camera 
}; //namespace rpl 







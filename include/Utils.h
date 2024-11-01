#pragma once

#include <vector> 
#include <Eigen/Core>
#include <Eigen/Dense>

#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp>   
#include <opencv2/imgcodecs.hpp> 

template<typename T>
void Cv2Eigen(const cv::Mat &image, Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> &eigen_mat){
    cv::cv2eigen(image, eigen_mat);
}


//convert a cv:Mat onbject into eigen based object 
// uing only fixed sizes matrixes and arrays 
//   cv::Mat image;
//   image = cv::imread("/dataset/images/15207_angle_image.jpg", CV_LOA D_IMAGE_GRAYSCALE);   // Read the file
//   Eigen::Matrix<float,Eigen::Dynamic, Eigen::Dynamic> eigen_mat;
//   cv::cv2eigen(image, eigen_mat);


// preprocess the image: normalize the lighting across a 
// single image using CLAHE (Contrast Limited Adaptive 
// Histogram Equalization)
void CLAHE(const cv::Mat image,cv::Mat& clahe_image,
        double clipLimit = 3.0, 
        cv::Size tileGridSize = cv::Size(8, 8)){

    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(clipLimit);
    clahe->setTilesGridSize(tileGridSize);
    clahe->apply(grayImage, clahe_image);
}
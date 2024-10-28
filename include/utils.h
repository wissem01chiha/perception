#pragma once

#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp>   
#include <opencv2/imgcodecs.hpp> 

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
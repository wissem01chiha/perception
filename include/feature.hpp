#pragma once

#include <vector>

#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp> 
#include <opencv2/xfeatures2d.hpp>


// scale-invariant feature transform
void getScaleInvariantFeatures(cv::Mat originalGrayImage){

    // for older versions of opencv
    //FeatureDetector* detector;
    
    //detector = new SiftFeatureDetector(
                    //                 0, // nFeatures
                 //                    4, // nOctaveLayers
                   //                  0.04, // contrastThreshold
                      //               10, //edgeThreshold
                    //                 1.6 //sigma
                     //                );
    // for newer hersions 
    std::vector<cv::KeyPoint> keypoints1;
    cv::Mat descriptors1;

    cv::Ptr<cv::xfeatures2d::SIFT> sift;
    sift = cv::xfeatures2d::SIFT::create (0,4,0.04,10,1.6);

    sift->detect(originalGrayImage, keypoints1);
    
    // Add results to image and save.
    cv::Mat output;
    cv::drawKeypoints(input, keypoints, output);
    cv::imwrite("sift_result.jpg", output);it.



}

//Asif alorithm : http://www.ipol.im/pub/art/2011/my-asift/
// comprehehsive study oh sift : 
// https://www.researchgate.net/publication/270268995_A_Comparative_Study_of_SIFT_and_its_Variants
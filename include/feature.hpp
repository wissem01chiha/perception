#pragma once

#include <vector>
#include <utility>
#include <omp.h>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp> 
#include <opencv2/features2d.hpp>  

#include "kdtree/kdtree.hpp"

std::pair<std::vector<std::vector<cv::KeyPoint>>, std::vector<cv::Mat>> 
getScaleInvariantFeatures(const std::vector<cv::Mat>& originalGrayImages,
                              int nfeatures =  250,
                              int nOctaveLayers = 4,
                              double contrastThreshold = 0.025,
                              double edgeThreshold = 9.0,
		                          double sigma = 1.4,
		                          bool  enable_precise_upscale = false ){
  
  cv::Ptr<cv::SIFT> detector = cv::SIFT::create(
        nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
    
  std::vector<std::vector<cv::KeyPoint>> keypoints(originalGrayImages.size());
  std::vector<cv::Mat> descriptors(originalGrayImages.size());

  for (size_t i = 0; i < originalGrayImages.size(); ++i) {
      detector->detect(originalGrayImages[i], keypoints[i]);
      detector->compute(originalGrayImages[i], keypoints[i], descriptors[i]);
  }
  return {keypoints,descriptors};
}

//compute structure invarient matching usig knn
// between 2 or more imagaes 
// 
void computeSIFMatching(std::vector<std::vector<cv::KeyPoint>> keyPoints,
                      std::vector<cv::Mat> descriptors ){

}
#include <chrono>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "../include/feature.hpp"

int main() {
    // Load two images (replace with your image paths)
    cv::Mat img1 = cv::imread("image1.jpg");
    cv::Mat img2 = cv::imread("image2.jpg");

    if (img1.empty() || img2.empty()) {
        std::cerr << "Error loading images!" << std::endl;
        return -1;
    }

    // Store images in a vector
    std::vector<cv::Mat> images = {img1, img2};

    auto start = std::chrono::high_resolution_clock::now();
    // Get keypoints and descriptors
    auto [keypoints, descriptors] = getScaleInvariantFeatures(images,9000);

    if (keypoints[0].empty()) {
        std::cerr << "No keypoints found in Image 1!" << std::endl;
    } else {
        std::cout << "Keypoints found in Image 1: " << keypoints[0].size() << std::endl;
    }

    if (keypoints[1].empty()) {
        std::cerr << "No keypoints found in Image 2!" << std::endl;
    } else {
        std::cout << "Keypoints found in Image 2: " << keypoints[1].size() << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
     std::chrono::duration<double> duration = end - start;

    // Display the duration
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
    // Draw keypoints on the images
    cv::Mat img1_keypoints, img2_keypoints;
    cv::drawKeypoints(img1, keypoints[0], img1_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DEFAULT); // Red
    cv::drawKeypoints(img2, keypoints[1], img2_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DEFAULT); // Red

    // Resize images for display
    int displayWidth = 1000;  // Desired width for display
    cv::Mat img1_keypoints_resized, img2_keypoints_resized;
    cv::resize(img1_keypoints, img1_keypoints_resized, cv::Size(displayWidth, img1_keypoints.rows * displayWidth / img1_keypoints.cols));
    cv::resize(img2_keypoints, img2_keypoints_resized, cv::Size(displayWidth, img2_keypoints.rows * displayWidth / img2_keypoints.cols));

    // Display the resized images with keypoints
    cv::imshow("Image 1 Keypoints", img1_keypoints_resized);
    cv::imshow("Image 2 Keypoints", img2_keypoints_resized);
    cv::imwrite("imgs_res1.jpg",img1_keypoints_resized);
    cv::imwrite("imgs_res2.jpg",img2_keypoints_resized);
    
    // Wait for a key press and close windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

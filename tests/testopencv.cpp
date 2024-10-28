#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Load an image from file
    std::string imagePath = "./image.png"; // Change this to your image path
    cv::Mat image = cv::imread(imagePath);

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // Display the original and grayscale images
    cv::imshow("Original Image", image);
    cv::imshow("Grayscale Image", grayImage);

    // Wait for a key press indefinitely
    cv::waitKey(0);

    return 0;
}

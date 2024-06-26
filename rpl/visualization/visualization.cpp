#include "opencv2/opencv.hpp"
#include <iostream>

int main() {
    // Read the image from a file
    cv::Mat image = cv::imread("fig.jpg");

    // Check if the image was successfully loaded
    if (image.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return 1;
    }

    // Convert the image to grayscale
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    // Display the original image
    cv::imshow("Original Image", image);

    // Display the grayscale image
    cv::imshow("Grayscale Image", gray_image);

    // Wait indefinitely for any key event
    cv::waitKey(0);

    // Destroy all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}

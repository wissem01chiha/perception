
#include <iostream>
#include <opencv2/highgui.hpp> 
#include "../include/preproc.hpp"

int main (){

  cv::Mat image = cv::imread("DSC00157.jpg");
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    //normalize_light(image);
    return 0;
}
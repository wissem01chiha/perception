
#include "../PTK/ThirdParty/CImg/CImg.h"

using namespace cimg_library;


int main() {
    // Load a JPEG image
    CImg<unsigned char> image("example.jpg"); // Replace "example.jpg" with your JPEG file path

    // Display the original image
    CImgDisplay display(image, "Original Image");

    // Convert the image to grayscale
    CImg<unsigned char> gray_image = image.get_RGBtoYCbCr().channel(0);

    // Display the grayscale image
    CImgDisplay gray_display(gray_image, "Grayscale Image");

    // Apply a Gaussian blur filter
    CImg<unsigned char> blurred_image = gray_image.get_blur(2.0);

    // Save the processed image as a new JPEG file
    blurred_image.save("processed_image.jpg");

    // Display the blurred image
    CImgDisplay blurred_display(blurred_image, "Blurred Image");

    // Keep the windows open until they are closed
    while (!display.is_closed() && !gray_display.is_closed() && !blurred_display.is_closed()) {
        display.wait();
        gray_display.wait();
        blurred_display.wait();
    }

    return 0;
}

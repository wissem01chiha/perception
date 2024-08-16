// run this command in terminal
// "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
// cl /EHsc main.cpp 
//
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "../PTK/ThirdParty/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../PTK/ThirdParty/stb/stb_image_write.h"

int main() {
    int width, height, channels;
    unsigned char *image = stbi_load("udem.png", &width, &height, &channels, 0);

    if (image == nullptr) {
        std::cerr << "Failed to load image\n";
        return -1;
    }

    // Print the size of the image
    std::cout << "Image loaded successfully\n";
    std::cout << "Width: " << width << " pixels\n";
    std::cout << "Height: " << height << " pixels\n";
    std::cout << "Channels: " << channels << "\n";

    // Create a grayscale image buffer
    unsigned char* grayscaleImage = new unsigned char[width * height];

    // Convert to grayscale if the image is RGB or RGBA
    if (channels >= 3) {
        for (int i = 0; i < width * height; ++i) {
            int r = image[i * channels + 0];
            int g = image[i * channels + 1];
            int b = image[i * channels + 2];
            grayscaleImage[i] = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
        }
    } else {
        // If the image is already grayscale, just copy the data
        std::copy(image, image + width * height, grayscaleImage);
    }

    // Save the grayscale image
    stbi_write_png("udem_grayscale.png", width, height, 1, grayscaleImage, width);

    // Free the image memory
    stbi_image_free(image);
    delete[] grayscaleImage;

    std::cout << "Grayscale image saved as udem_grayscale.png\n";

    return 0;
}

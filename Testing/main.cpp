// "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
// cl /EHsc main.cpp 
//
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "../RPL/ThirdParty/stb/stb_image.h"

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

    // Process the image data
    stbi_image_free(image);
    
    return 0;
}

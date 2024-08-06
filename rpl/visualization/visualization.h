#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "../../external/stb/stb_image.h"

int main() {
  int width, height, channels;
unsigned char *image = stbi_load("image.png", &width, &height, &channels, 0);

if (image == nullptr) {
    std::cerr << "Failed to load image\n";
    return -1;
}

// Process the image data
stbi_image_free(image);
}

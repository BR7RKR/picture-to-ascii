#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("ERROR: provide exactly one argument that contains path to the file\n");
        return 1;
    }
    
    const int MAX_BRIGHTNESS = 255;
    const char ascii_chars[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    int ascii_chars_size = sizeof(ascii_chars)/sizeof(char);
    
    int img_width, img_height, channels;
    char *path_to_img = argv[1];
    printf("INFO: file path: %s\n", path_to_img);
    
    unsigned char* img = stbi_load(path_to_img, &img_width, &img_height, &channels, 1);
    
    if (!img) {
        printf("ERROR: Failed to read the image\n");
        return 2;
    }
    
    size_t width = img_width;
    size_t height = img_height;
    
    float width_scale = 0.6f; // TODO: use aspect ratio to scale the image
    float height_scale = 0.3f;
    size_t comp_width  = (size_t)(width * width_scale);
    size_t comp_height = (size_t)(height * height_scale);
    size_t ascii_img_size = comp_width * comp_height * 1;
    char *ascii_img = calloc(ascii_img_size, sizeof(char));
    
    if (!ascii_img) {
        printf("ERROR: Failed to allocate memory for the ascii_img\n");
        return 2;
    }

    for (size_t y = 0; y < comp_height; y++) {
        for (size_t x = 0; x < comp_width; x++) {
            size_t src_x = (size_t)(x * ((float)width / comp_width));
            if (src_x >= width) src_x = width - 1;

            size_t src_y = (size_t)(y * ((float)height / comp_height));
            if (src_y >= height) src_y = height - 1;

            size_t idx = src_y * width + src_x;
            int brightness = img[idx];
            int symbol_index = (int)(brightness * (ascii_chars_size-1) / MAX_BRIGHTNESS);
            ascii_img[y * comp_width + x] = ascii_chars[symbol_index];
        }
    }
    
    for (size_t y = 0; y < comp_height; y++) {
        for (size_t x = 0; x < comp_width; x++) {
            putchar(ascii_img[y * comp_width + x]);
        }
        putchar('\n');
    }
    
    if (img) {
        stbi_image_free(img);
    }
    
    if (ascii_img) {
        free(ascii_img);
    }

    return 0;
}


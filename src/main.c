#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "converter.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 3) {
        printf("ERROR: provide exactly one argument that contains path to the file\n");
        return 1;
    }
    
    const char ascii_chars[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    int ascii_chars_size = sizeof(ascii_chars)/sizeof(char) - 1; // minus one to avoid \0 symbol
    struct Converter *conv = Converter_create(ascii_chars, ascii_chars_size, 0.6f, 0.3f);
    
    if (!conv) {
        printf("ERROR: Failed to create Converter\n");
        return 2;
    }
    
    int img_width, img_height, channels;
    char *path_to_img = argv[1];
    char *path_to_save = argv[2];
    printf("INFO: file path: %s\n", path_to_img);
    
    unsigned char* img = stbi_load(path_to_img, &img_width, &img_height, &channels, 1);
    
    if (!img) {
        printf("ERROR: Failed to read the image\n");
        return 3;
    }
    
    struct AsciiImg *ascii_img = convert_img_to_ascii(conv, img, img_width, img_height);
    
    if (!ascii_img) {
        printf("ERROR: Failed to convert picture to ascii image\n");
        return 4;
    }

    AsciiImg_print(ascii_img);
    
    int result = AsciiImg_save_to_file(ascii_img, path_to_save);
    
    if (img) {
        stbi_image_free(img);
    }
    
    if (conv) {
        Converter_free(conv);
    }
    
    if (ascii_img) {
        AsciiImg_free(ascii_img);
    }
    
    if (result != 0) {
        printf("ERROR failed to save ascii image to file\n");
        return result;
    }

    return 0;
}


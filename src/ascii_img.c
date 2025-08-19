#include "ascii_img.h"

#include <stdlib.h>
#include <string.h>

struct AsciiImg *AsciiImg_create(const char *data, size_t width, size_t height){
    if (!data) {
        return NULL;
    }
    
    if (!width) {
        return NULL;
    }
    
    if (!height) {
        return NULL;
    }
    
    struct AsciiImg *ascii_img = malloc(sizeof(struct AsciiImg));
    
    if (!ascii_img) {
        return NULL;
    }
    
    ascii_img->width = width;
    ascii_img->height = height;
    ascii_img->img = calloc(width * height, sizeof(char));
    
    if (!ascii_img->img) {
        AsciiImg_free(ascii_img);
        return NULL;
    }
    
    memcpy(ascii_img->img, data, width * height * sizeof(char));
    
    return ascii_img;
}

void AsciiImg_free(struct AsciiImg *img){
    if (!img) {
        return;
    }
    
    if (img->img) {
        free(img->img);
    }
    
    img->width = 0;
    img->height = 0;
    
    free(img);
}

void AsciiImg_print(struct AsciiImg *img){
    if (!img) {
        return;
    }
    
    for (size_t y = 0; y < img->height; y++) {
        for (size_t x = 0; x < img->width; x++) {
            putchar(img->img[y * img->width + x]);
        }
        putchar('\n');
    }
}

int AsciiImg_save_to_file(struct AsciiImg *img, const char* path){
    if (!img) {
        return -1;
    }
    
    FILE *save_file = fopen(path, "wb");
    
    if (!save_file) {
        return -3;
    }
    
    for (size_t y = 0; y < img->height; y++) {
        for (size_t x = 0; x < img->width; x++) {
            int res = putc(img->img[y * img->width + x], save_file);
            
            if (res == EOF) { // TODO: test more save to file
                return EOF;
            }
        }
        int res = putc('\n', save_file);
        
        if (res == EOF) {
            return EOF;
        }
    }
    
    if (save_file) {
        return fclose(save_file);
    }
    
    return 0;
}

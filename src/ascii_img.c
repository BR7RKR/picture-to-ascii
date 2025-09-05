#include "global.h"
#include "ascii_img.h"
#include "stb_image_write.h"

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

struct AsciiImg *AsciiImg_create_from_img(struct ConverterConfig *cfg, unsigned char *img, size_t width, size_t height){
    if (!cfg) {
        return NULL;
    }
    
    if (!img) {
        return NULL;
    }
    
    if (width <= 0) {
        return NULL;
    }
    
    if (height <= 0) {
        return NULL;
    }
    
    float width_scale = cfg->width_scale;
    float height_scale = cfg->height_scale;
    size_t comp_width  = (size_t)(width * width_scale);
    size_t comp_height = (size_t)(height * height_scale);
    size_t ascii_img_size = comp_width * comp_height * 1;
    char *ascii_img = calloc(ascii_img_size, sizeof(char));
    
    if (!ascii_img) {
        return NULL;
    }

    #pragma omp parallel for schedule(static)
    for (size_t y = 0; y < comp_height; y++) {
        for (size_t x = 0; x < comp_width; x++) {
            size_t src_x = (size_t)(x * ((float)width / comp_width));
            if (src_x >= width) src_x = width - 1;

            size_t src_y = (size_t)(y * ((float)height / comp_height));
            if (src_y >= height) src_y = height - 1;

            size_t idx = src_y * width + src_x;
            int brightness = img[idx];
            int symbol_index = (int)(brightness * (cfg->ascii_chars_size-1) / MAX_BRIGHTNESS);
            ascii_img[y * comp_width + x] = cfg->ascii_chars[symbol_index];
        }
    }
    
    struct AsciiImg *ascii = AsciiImg_create(ascii_img, comp_width, comp_height);
    
    free(ascii_img);
    return ascii;
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
            
            if (res == EOF) {
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

int AsciiImg_save_to_file_image(struct AsciiImg *img, const char* path_to_image, struct Font *font){
    if (!img) {
        return -1;
    }
    
    const int channels = 1; // grey
    const size_t img_w = img->width * font->symbol_width;
    const size_t img_h = img->height * font->symbol_height;
    unsigned char *pixels = calloc(img_w * img_h, channels);
    
    if (!pixels) {
        return -2;
    }
     
    #pragma omp parallel for schedule(static)
    for (size_t y = 0; y < img->height; y++) {
        for (size_t x = 0; x < img->width; x++) {
            unsigned char c = (unsigned char)img->img[y * img->width + x];
            unsigned char *glyph = (unsigned char *)font->map[c]; // TODO: try to convert all symbols into an array of brightness
            
            for (size_t gy = 0; gy < font->symbol_height; gy++) {
                for (size_t gx = 0; gx < font->symbol_width; gx++) {
                    int bit = (glyph[gy] >> gx) & 1; // move by gx bits and take the bit from the right position
                    if (bit) {
                        size_t px = x * font->symbol_width + gx;
                        size_t py = y * font->symbol_height + gy;
                        pixels[py * img_w + px] = MAX_BRIGHTNESS;
                    }
                }
            }
        }
    }

    FileType fileType = get_file_extension(path_to_image);
    
    int res = 0;
    switch (fileType) {
        case FILE_JPEG:
            res = stbi_write_jpg(path_to_image, (int)img_w, (int)img_h, channels, pixels, (int)img_w * channels);
            break;
            
        case FILE_PNG:
            res = stbi_write_png(path_to_image, (int)img_w, (int)img_h, channels, pixels, (int)img_w * channels);
            break;
            
        case FILE_TGA:
            res = stbi_write_tga(path_to_image, (int)img_w, (int)img_h, channels, pixels);
            break;
            
        case FILE_BMP:
            res = stbi_write_bmp(path_to_image, (int)img_w, (int)img_h, channels, pixels);
            break;
        
        case FILE_TXT:
        case FILE_NAF:
        default:
            res = -3;
            break;
    }

    
    free(pixels);
    
    if (!res || res == -3) {
        return -3;
    }
    
    return 0;
}

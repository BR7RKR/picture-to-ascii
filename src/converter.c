#include "converter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_BRIGHTNESS = 255;

struct Converter *Converter_create(const char *ascii_chars,
                                   int ascii_chars_size,
                                   float width_scale,
                                   float height_scale)
{
    if (!ascii_chars) {
        return NULL;
    }
    
    if (ascii_chars_size <= 0) {
        return NULL;
    }
    
    if (width_scale <= 0) {
        return NULL;
    }
    
    if (height_scale <= 0) {
        return NULL;
    }
    
    struct Converter *conv = malloc(sizeof(struct Converter));
    
    if (!conv) {
        return NULL;
    }
    
    conv->ascii_chars = calloc(ascii_chars_size, sizeof(char));
    
    if (!conv->ascii_chars) {
        Converter_free(conv);
        return NULL;
    }
    
    memcpy(conv->ascii_chars, ascii_chars, ascii_chars_size);
    
    conv->ascii_chars_size=ascii_chars_size;
    conv->height_scale = height_scale;
    conv->width_scale = width_scale;
    
    return conv;
}

void Converter_free(struct Converter *converter){
    if (!converter) {
        return;
    }
    
    if (converter->ascii_chars) {
        free(converter->ascii_chars);
    }
    
    converter->ascii_chars_size = 0;
    converter->height_scale = 0;
    converter->width_scale = 0;
    
    free(converter);
}

struct AsciiImg *convert_img_to_ascii(struct Converter *conv, unsigned char *img, size_t width, size_t height){
    if (!conv) {
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
    
    float width_scale = conv->width_scale;
    float height_scale = conv->height_scale;
    size_t comp_width  = (size_t)(width * width_scale);
    size_t comp_height = (size_t)(height * height_scale);
    size_t ascii_img_size = comp_width * comp_height * 1;
    char *ascii_img = calloc(ascii_img_size, sizeof(char));
    
    if (!ascii_img) {
        return NULL;
    }

    for (size_t y = 0; y < comp_height; y++) {
        for (size_t x = 0; x < comp_width; x++) {
            size_t src_x = (size_t)(x * ((float)width / comp_width));
            if (src_x >= width) src_x = width - 1;

            size_t src_y = (size_t)(y * ((float)height / comp_height));
            if (src_y >= height) src_y = height - 1;

            size_t idx = src_y * width + src_x;
            int brightness = img[idx];
            int symbol_index = (int)(brightness * (conv->ascii_chars_size-1) / MAX_BRIGHTNESS);
            ascii_img[y * comp_width + x] = conv->ascii_chars[symbol_index];
        }
    }
    
    struct AsciiImg *ascii = AsciiImg_create(ascii_img, comp_width, comp_height);
    
    if (ascii_img) {
        free(ascii_img);
    }
    
    return ascii;
}

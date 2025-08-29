#include "converter.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_BRIGHTNESS = 255;

struct ConverterConfig ConverterConfig_create(const char *ascii_chars, size_t ascii_chars_size, float width_scale, float height_scale){
    struct ConverterConfig cfg = {0};
    
    if (!ascii_chars) {
        return cfg;
    }
    
    if (ascii_chars_size <= 0) {
        return cfg;
    }
    
    if (width_scale < 0 || is_equalf(width_scale, 0)) {
        return cfg;
    }
    
    if (height_scale < 0 || is_equalf(height_scale, 0)) {
        return cfg;
    }
    
    cfg.ascii_chars = ascii_chars;
    cfg.ascii_chars_size=ascii_chars_size;
    cfg.height_scale = height_scale;
    cfg.width_scale = width_scale;
    
    return cfg;
}

struct AsciiImg *convert_img_to_ascii(struct ConverterConfig *cfg, unsigned char *img, size_t width, size_t height){
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
    
    if (ascii_img) {
        free(ascii_img);
    }
    
    return ascii;
}

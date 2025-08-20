#pragma once

#include "ascii_img.h"

struct ConverterConfig{
    const char *ascii_chars; // NOTE: \0 must not be counted
    size_t ascii_chars_size;
    float width_scale;
    float height_scale;
};


struct ConverterConfig ConverterConfig_create(const char *ascii_chars, size_t ascii_chars_size, float width_scale, float height_scale);

struct AsciiImg *convert_img_to_ascii(struct ConverterConfig *cfg, unsigned char *img, size_t width, size_t height);

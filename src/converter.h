#pragma once

#include "ascii_img.h"

struct Converter{
    char *ascii_chars; // NOTE: I consider thar char * here is not a string
    int ascii_chars_size; // NOTE: do minus 1 if you use ascii_chars as a sting to avoid \0 symbol
    float width_scale;
    float height_scale;
};

struct Converter *Converter_create(const char *ascii_chars,
                                   int ascii_chars_size,
                                   float width_scale,
                                   float height_scale);
void Converter_free(struct Converter *converter);

struct AsciiImg *convert_img_to_ascii(struct Converter *conv, unsigned char *img, size_t width, size_t height);

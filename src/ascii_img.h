#pragma once

#include <stdio.h>
#include "converter_cfg.h"

struct AsciiImg{
    char *img;
    size_t height;
    size_t width;
};

struct Font{
    char **map;
    size_t symbols_count;
    size_t symbol_width;
    size_t symbol_height;
};

struct AsciiImg *AsciiImg_create(const char *data, size_t width, size_t height);
struct AsciiImg *AsciiImg_create_from_img(struct ConverterConfig *cfg, unsigned char *img, size_t width, size_t height);
void AsciiImg_free(struct AsciiImg *img);

void AsciiImg_print(struct AsciiImg *img);
int AsciiImg_save_to_file(struct AsciiImg *img, const char* path);
int AsciiImg_save_to_file_image(struct AsciiImg *img, const char* path, struct Font *font);

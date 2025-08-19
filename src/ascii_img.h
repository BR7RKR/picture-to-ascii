#pragma once

#include <stdio.h>

struct AsciiImg{
    char *img;
    size_t height;
    size_t width;
};

struct AsciiImg *AsciiImg_create(const char *data, size_t width, size_t height);
void AsciiImg_free(struct AsciiImg *img);

void AsciiImg_print(struct AsciiImg *img);
int AsciiImg_save_to_file(struct AsciiImg *img, const char* path);

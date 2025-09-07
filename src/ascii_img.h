#pragma once
#include "converter_cfg.h"
#include "font.h"

#include <stdio.h>

typedef enum{
    ASCII_IMG_OK = 0,
    ASCII_IMG_OK_TURBO_JPEG = 1,
    
    ASCII_IMG_ERR = -404,              // UNKNOWN ERROR
    ASCII_IMG_ERR_NULL = -1,
    ASCII_IMG_ERR_FILE_FOPEN = -2,
    ASCII_IMG_ERR_FILE_SAVE = -3,
    ASCII_IMG_ERR_ALLOC = -4,
} AsciiImgResult;

struct AsciiImg{
    char *img;
    size_t height;
    size_t width;
};

struct AsciiImg *AsciiImg_create(const char *data, size_t width, size_t height);
struct AsciiImg *AsciiImg_create_from_img(struct ConverterConfig *cfg, unsigned char *img, size_t width, size_t height);
void AsciiImg_free(struct AsciiImg *img);

void AsciiImg_print(struct AsciiImg *img);
int AsciiImg_save_to_file(struct AsciiImg *img, const char* path);
int AsciiImg_save_to_file_image(struct AsciiImg *img, const char* path, struct Font *font);

#pragma once
#include "converter_cfg.h"
#include "font.h"

typedef enum{
    ASCII_IMG_OK = 0,
    ASCII_IMG_OK_TURBO_JPEG = 1,
    
    ASCII_IMG_ERR = -404,              // UNKNOWN ERROR
    ASCII_IMG_ERR_NULL = -1,
    ASCII_IMG_ERR_FILE_FOPEN = -2,
    ASCII_IMG_ERR_FILE_SAVE = -3,
    ASCII_IMG_ERR_ALLOC = -4,
    ASCII_IMG_ERR_EOF = -5,
    ASCII_IMG_ERR_FCLOSE = -6
} AsciiImgResult;

struct AsciiImg{
    char *img;
    size_t height;
    size_t width;
};

struct AsciiImg *AsciiImg_create(const char *restrict data, size_t width, size_t height);
struct AsciiImg *AsciiImg_create_from_img(struct ConverterConfig *restrict cfg, unsigned char *restrict img, size_t width, size_t height);
void AsciiImg_free(struct AsciiImg *restrict img);

void AsciiImg_print(struct AsciiImg *restrict img);
AsciiImgResult AsciiImg_save_to_file(struct AsciiImg *restrict img, const char *restrict path_to_image, struct Font *restrict font);

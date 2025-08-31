#pragma once
#include <stdbool.h>

typedef enum {
    FILE_NAF = 0,   // Not a file
    
    FILE_TXT = 1,
    FILE_JPEG = 2,
    FILE_PNG = 3,
    FILE_TGA = 4,
    FILE_BMP = 5,
    FILE_PSD = 6,
    FILE_GIF = 7,   // (only a single frame, not an animation)
    FILE_HDR = 8,
    FILE_PIC = 9,
    FILE_PNM = 10   // (PPM/PGM)
} FileType;

extern const int MAX_BRIGHTNESS;

bool is_equalf(float first, float second);

FileType get_file_extension(const char *path_to_file);

#pragma once
#include <stdbool.h>

#include "logger.h"

typedef enum {
    FILE_NAF = 0,   // Not a file
    
    FILE_TXT = 1,
    FILE_JPEG = 2,
    FILE_PNG = 3,
    FILE_TGA = 4,
    FILE_BMP = 5,
} FileType;

extern const int MAX_BRIGHTNESS;

bool is_equalf(float first, float second);

FileType get_file_extension(const char *restrict path_to_file);

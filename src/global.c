#include <math.h>
#include <string.h>

#include "global.h"

const int MAX_BRIGHTNESS = 255;

bool is_equalf(float first, float second){
    float epsilon = 1e-6f;
    return fabsf(first - second) <= epsilon * fmaxf(fabsf(first), fabsf(second));
}

FileType get_file_extension(const char *restrict path_to_file){
    if (!path_to_file) {
        debug("Path is null");
        return FILE_NAF;
    }
    
    char *dot = strrchr(path_to_file, '.');
    char *ext = ++dot;
    
    if (strcmp(ext, "txt") == 0) {
        debug("Path is txt file");
        return FILE_TXT;
    }
    
    if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0) {
        debug("Path is jpeg file");
        return FILE_JPEG;
    }
    
    if (strcmp(ext, "png") == 0) {
        debug("Path is png file");
        return FILE_PNG;
    }
    
    if (strcmp(ext, "tga") == 0
        || strcmp(ext, "icb") == 0
        || strcmp(ext, "vda") == 0
        || strcmp(ext, "vst") == 0) {
            debug("Path is tga file");
            return FILE_TGA;
    }
    
    if (strcmp(ext, "bmp") == 0
        || strcmp(ext, "dip") == 0
        || strcmp(ext, "rle") == 0) {
            debug("Path is bmp file");
            return FILE_BMP;
    }
    
    debug("Path is not a file");
    return FILE_NAF;
}


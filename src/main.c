#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#pragma GCC diagnostic pop

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "converter_cfg.h"
#include "global.h"
#include "compcodes.h"
#include "ascii_img.h"
#include "font8x8_basic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

char* str_rev(const char *in_str);
int float_parse(const char *str, float *out_value);
void print_help(void);

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("ERROR: wrong amount of arguments.\n\n");
        printf("Use --help or -h flag to get more information\n");
        return PTS_ERR_NOT_ENOUGH_ARGS;
    }
    
    // TODO: Create Font_create method
    struct Font default_font = {NULL, 128, 8, 8};

    default_font.map = malloc(default_font.symbols_count * sizeof(char*));

    for (size_t i = 0; i < default_font.symbols_count; i++) {
        default_font.map[i] = font8x8_basic[i];
    }
    //
    
    const char *default_ascii_chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. "; // it is array not a string
    const size_t default_ascii_chars_size = strlen(default_ascii_chars)-1;
    
    const char *default_ascii_chars_light = "@%#*+=-:. "; // it is array not a string
    const size_t default_ascii_chars_light_size = strlen(default_ascii_chars_light) - 1;
    
    const float default_width_scale = 0.6f;
    const float default_height_scale = 0.3f;
    
    bool is_reverse = false;
    bool is_print_to_console = false;
    bool is_light = false;
    char *path_to_save = NULL;
    char *path_to_save_img = NULL;
    char *path_to_img = NULL;
    float width_scale = 0;
    float height_scale = 0;
    char *ascii_chars = NULL;
    size_t ascii_chars_size = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return PTS_OK;
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--print") == 0) {
            is_print_to_console = true;
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (argc <= i+1) {
                printf("ERROR: not enough args\n");
                return PTS_ERR_NOT_ENOUGH_ARGS;
            }
            
            path_to_save = argv[i+1];
        } else if (strcmp(argv[i], "-ws") == 0 || strcmp(argv[i], "--width-scale") == 0) {
            if (argc <= i+1) {
                printf("ERROR: not enough args\n");
                return PTS_ERR_NOT_ENOUGH_ARGS;
            }
            
            int result = float_parse(argv[i+1], &width_scale);
            if (result == PTS_ERR_FLOAT_PARSE) {
                printf("ERROR: failed to parse float\n");
                return result;
            }
        } else if (strcmp(argv[i], "-hs") == 0 || strcmp(argv[i], "--height-scale") == 0) {
            if (argc <= i+1) {
                printf("ERROR: not enough args\n");
                return PTS_ERR_NOT_ENOUGH_ARGS;
            }
            
            int result = float_parse(argv[i+1], &height_scale);
            if (result == PTS_ERR_FLOAT_PARSE) {
                printf("ERROR: failed to parse float\n");
                return result;
            }
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--symbols") == 0) {
            if (argc <= i+1) {
                printf("ERROR: not enough args\n");
                return PTS_ERR_NOT_ENOUGH_ARGS;
            }
            
            ascii_chars = argv[i+1];
            ascii_chars_size = strlen(ascii_chars)-1; // -1 is used to avoid \0
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--image") == 0) {
            if (argc <= i+1) {
                printf("ERROR: not enough args\n");
                return PTS_ERR_NOT_ENOUGH_ARGS;
            }

            path_to_img = argv[i+1];
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lite") == 0) {
            is_light = true;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--reverse") == 0) {
            is_reverse = true;
        } else if (strcmp(argv[i], "-if") == 0 || strcmp(argv[i], "--image-file") == 0) {
            if (argc <= i+1) {
                printf("ERROR: not enough args\n");
                return PTS_ERR_NOT_ENOUGH_ARGS;
            }
            
            path_to_save_img = argv[i+1];
        }
    }
    
    if (!path_to_img) {
        printf("ERROR: path must be provided\n");
        print_help();
        return PTS_ERR_IMG_PATH;
    }
    
    width_scale = is_equalf(width_scale, 0) ? default_width_scale : width_scale;
    height_scale = is_equalf(height_scale, 0) ? default_height_scale : height_scale;
    
    if (!ascii_chars) {
        if (is_light) {
            ascii_chars = (char *) default_ascii_chars_light;
            ascii_chars_size = default_ascii_chars_light_size;
        } else {
            ascii_chars = (char *) default_ascii_chars;
            ascii_chars_size = default_ascii_chars_size;
        }
    }
    
    char *temp_ascii_chars = NULL;
    if (is_reverse) {
        temp_ascii_chars = str_rev(ascii_chars);
        ascii_chars = temp_ascii_chars;
    }
    
    struct ConverterConfig cfg = ConverterConfig_create(ascii_chars, ascii_chars_size, width_scale, height_scale);
    
    if (!cfg.ascii_chars) {
        printf("ERROR: Failed to create converter config\n");
        return PTS_ERR_CFG_CREATION;
    }
    
    int img_width, img_height, channels;
    unsigned char* img = stbi_load(path_to_img, &img_width, &img_height, &channels, 1);
    
    if (!img) {
        printf("ERROR: Failed to read the image\n");
        return PTS_ERR_IMG_READ;
    }
    
    struct AsciiImg *ascii_img = AsciiImg_create_from_img(&cfg, img, img_width, img_height);
    
    if (!ascii_img) {
        printf("ERROR: Failed to convert picture to ascii image\n");
        return PTS_ERR_CONVERT;
    }
    
    if (is_print_to_console) {
        AsciiImg_print(ascii_img);
        printf("INFO: ascii image was printed successfully\n");
    }
    
    int result = PTS_OK;
    if (path_to_save) {
        result = AsciiImg_save_to_file(ascii_img, path_to_save);
        if (result != ASCII_IMG_OK) {
            printf("ERROR failed to save ascii image to file\n");
        } else {
            printf("INFO: ascii image was saved successfully\n");
        }
    }
    
    if (path_to_save_img) {
        result = AsciiImg_save_to_file_image(ascii_img, path_to_save_img, &default_font);
        if (result != ASCII_IMG_OK) {
            printf("ERROR failed to save ascii image as an image\n");
        } else {
            printf("INFO: ascii image was saved successfully as an image\n");
        }
    }
    
    stbi_image_free(img);
    AsciiImg_free(ascii_img);
    free(temp_ascii_chars);
    free(default_font.map);
    
    if (result != PTS_OK) {
        return PTS_ERR_SAVE_TXT;
    }

    return result;
}

char* str_rev(const char *in_str) {
    size_t len = strlen(in_str);
    char *out_str = calloc(len + 1, sizeof(char)); // +1 for '\0'
    if (!out_str) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        out_str[i] = in_str[len - 1 - i];
    }
    
    out_str[len] = '\0';
    return out_str;
}

void print_help(void){
    printf("Usage: pictoascii [options]\n\n");
    printf("Options:\n");
    printf("  -h, --help                Show this help message and exit\n");
    printf("  -p, --print               Print output to console\n");
    printf("  -f, --file <path>         Save output to file at specified path\n");
    printf("  -i, --image <path>        Path to input image file\n");
    printf("  -s, --symbols <chars>     Specify custom ASCII characters for output\n");
    printf("  -ws, --width-scale <f>    Scale width by a float factor (e.g., 0.5)\n");
    printf("  -hs, --height-scale <f>   Scale height by a float factor (e.g., 0.5)\n");
    printf("  -l, --lite                Use simple ascii characters for outputm\n");
    printf("  -r, --reverse             Reverse symbols that are used to draw the image\n");
    printf("  -if, --image-file <path>  Save output to file at specified path as an image\n");
    printf("\n");
    printf("Examples:\n");
    printf("  pictoascii -p -i image.png -f output.txt\n");
    printf("  pictoascii --image image.png --lite -p\n");
}

int float_parse(const char *str, float *out_value){
    errno = 0;
    float number = strtof(str, NULL);
    *out_value = 0;
    
    if (errno == ERANGE) {
        return PTS_ERR_FLOAT_PARSE;
    }
    
    if (is_equalf(number, 0.0f)) {
        return PTS_ERR_FLOAT_PARSE;
    }
    
    if (number < 0.0f) {
        return PTS_ERR_FLOAT_PARSE;
    }
    
    *out_value = number;
    return PTS_OK;
}

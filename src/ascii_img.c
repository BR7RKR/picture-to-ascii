#include <stdlib.h>
#include <string.h>
#include <turbojpeg.h>

#include "global.h"
#include "ascii_img.h"
#include "stb_image_write.h"

static AsciiImgResult write_gray_jpg(const char *restrict path, int width, int height, unsigned char *restrict buffer);
static AsciiImgResult save_as_image(struct AsciiImg *restrict img, const char *restrict path, struct Font *restrict font);
static AsciiImgResult save_as_txt(struct AsciiImg *restrict img, const char *restrict path);

struct AsciiImg *AsciiImg_create(const char *restrict data, size_t width, size_t height){
    if (!data) {
        debug("Data is null");
        return NULL;
    }
    
    if (!width) {
        debug("Width is null");
        return NULL;
    }
    
    if (!height) {
        debug("Height is null");
        return NULL;
    }
    
    struct AsciiImg *ascii_img = malloc(sizeof(*ascii_img));
    
    if (!ascii_img) {
        log_error("Failed to allocate memory for the ascii_img");
        return NULL;
    }
    
    ascii_img->width = width;
    ascii_img->height = height;
    ascii_img->img = calloc(width * height, sizeof(char));
    
    if (!ascii_img->img) {
        log_error("Failed to allocate memory for the ascii_img->img");
        AsciiImg_free(ascii_img);
        return NULL;
    }
    
    memcpy(ascii_img->img, data, width * height * sizeof(char));
    
    log_info("AsciiImg was created successfully");
    return ascii_img;
}

struct AsciiImg *AsciiImg_create_from_img(struct ConverterConfig *restrict cfg, unsigned char *restrict img, size_t width, size_t height){
    if (!cfg) {
        debug("Cfg is null");
        return NULL;
    }
    
    if (!img) {
        debug("Img is null");
        return NULL;
    }
    
    if (width <= 0) {
        debug("Width is null");
        return NULL;
    }
    
    if (height <= 0) {
        debug("Height is null");
        return NULL;
    }
    
    float width_scale = cfg->width_scale;
    float height_scale = cfg->height_scale;
    size_t comp_width  = (size_t)(width * width_scale);
    size_t comp_height = (size_t)(height * height_scale);
    size_t ascii_img_size = comp_width * comp_height * 1;
    char *restrict ascii_img = calloc(ascii_img_size, sizeof(char));
    
    if (!ascii_img) {
        log_error("Failed to allocate memory for the ascii_img pixels");
        return NULL;
    }

    #pragma omp parallel for schedule(static)
    for (size_t y = 0; y < comp_height; y++) {
        for (size_t x = 0; x < comp_width; x++) {
            size_t src_x = (size_t)(x * ((float)width / comp_width));
            if (src_x >= width) src_x = width - 1;

            size_t src_y = (size_t)(y * ((float)height / comp_height));
            if (src_y >= height) src_y = height - 1;

            size_t idx = src_y * width + src_x;
            int brightness = img[idx];
            int symbol_index = (int)(brightness * (cfg->ascii_chars_size-1) / MAX_BRIGHTNESS);
            ascii_img[y * comp_width + x] = cfg->ascii_chars[symbol_index];
        }
    }
    
    struct AsciiImg *ascii = AsciiImg_create(ascii_img, comp_width, comp_height);
    
    free(ascii_img);
    log_info("AsciiImg was created successfully from image file");
    return ascii;
}

void AsciiImg_free(struct AsciiImg *restrict img){
    if (!img) {
        return;
    }
    
    if (img->img) {
        free(img->img);
    }
    
    img->width = 0;
    img->height = 0;
    
    free(img);
}

void AsciiImg_print(struct AsciiImg *restrict img){
    if (!img) {
        debug("Img is null");
        return;
    }
    
    for (size_t y = 0; y < img->height; y++) {
        for (size_t x = 0; x < img->width; x++) {
            putchar(img->img[y * img->width + x]);
        }
        putchar('\n');
    }
    log_info("Ascii image was printed successfully");
}

AsciiImgResult AsciiImg_save_to_file(struct AsciiImg *restrict img, const char *restrict path_to_save, struct Font *restrict font){
    if (!img || !path_to_save)
    {
        log_error("AsciiImg or path is null");
        return ASCII_IMG_ERR_NULL;
    }
    
    FileType fileType = get_file_extension(path_to_save);

    if (fileType == FILE_TXT)
    {
        return save_as_txt(img, path_to_save);
    }
    
    if (fileType == FILE_NAF)
    {
        return ASCII_IMG_ERR_FILE_SAVE;
    }

    if (!font)
    {
        return ASCII_IMG_ERR_NULL;
    }

    return save_as_image(img, path_to_save, font);
}

AsciiImgResult save_as_txt(struct AsciiImg *restrict img, const char *restrict path){
    if (!img || !path) {

        log_error("AsciiImg or path is null");
        return ASCII_IMG_ERR_NULL;
    }
    
    FILE *save_file = fopen(path, "wb");
    
    if (!save_file) {
        log_error("Unable to open file for writing");
        return ASCII_IMG_ERR_FILE_FOPEN;
    }
    
    for (size_t y = 0; y < img->height; y++) {
        for (size_t x = 0; x < img->width; x++) {
            int res = putc(img->img[y * img->width + x], save_file);
            
            if (res == EOF) {
                fclose(save_file);
                debug("Failed to save image as text in x loop");
                return ASCII_IMG_ERR_EOF;
            }
        }
        int res = putc('\n', save_file);
        
        if (res == EOF) {
            fclose(save_file);
            debug("Failed to save image as text in y loop");
            return ASCII_IMG_ERR_EOF;
        }
    }
    
    if (fclose(save_file) != 0) {
        log_error("Failed to close txt file");
        return ASCII_IMG_ERR_FCLOSE;
    }
    
    log_info("AsciiImg was saved as txt file");
    return ASCII_IMG_OK;
}

AsciiImgResult save_as_image(struct AsciiImg *restrict img, const char *restrict path_to_image, struct Font *restrict font){
    if (!img || !font || !font->map) {
        log_error("AsciiImg or font is null");
        return ASCII_IMG_ERR_NULL;
    }

    const int channels = 1; // grey
    const size_t img_w = img->width * font->symbol_width;
    const size_t img_h = img->height * font->symbol_height;

    unsigned char *restrict pixels = calloc(img_w * img_h, channels);
    if (!pixels) {
        log_error("Unable to allocate memory for image pixels");
        return ASCII_IMG_ERR_ALLOC;
    }

    size_t bytes_per_row = (font->symbol_width + 7) / 8;
    
    #pragma omp parallel for schedule(static)
    for (size_t y = 0; y < img->height; y++) {
        for (size_t x = 0; x < img->width; x++) {
            unsigned char c = (unsigned char)img->img[y * img->width + x]; // TODO: make tiles for all symbols before this method

            if (c >= font->symbols_count) {
                log_warning("Unable to find matching symbol in font");
                continue;
            }

            unsigned char *restrict glyph = (unsigned char *)font->map[c];
            
            for (size_t gy = 0; gy < font->symbol_height; gy++) {
                unsigned char *restrict row_ptr = &glyph[gy * bytes_per_row];
                
                for (size_t gx = 0; gx < font->symbol_width; gx++) {
                    int bit = (row_ptr[gx / 8] >> (7 - (gx % 8))) & 1;

                    if (bit) {
                        size_t px = x * font->symbol_width + gx;
                        size_t py = y * font->symbol_height + gy;
                        pixels[py * img_w + px] = MAX_BRIGHTNESS;
                    }
                }
            }
        }
    }

    FileType fileType = get_file_extension(path_to_image);
    int res = ASCII_IMG_OK;

    switch (fileType) {
        case FILE_JPEG:
            log_info("Saving AsciiImg as jpeg...");
            res = write_gray_jpg(path_to_image, (int)img_w, (int)img_h, pixels);
            log_info("Saved AsciiImg as jpeg");
            break;
        case FILE_PNG:
            log_info("Saving AsciiImg as png...");
            res = stbi_write_png(path_to_image, (int)img_w, (int)img_h, channels, pixels, (int)img_w * channels);
            log_info("Saved AsciiImg as png");
            break;
        case FILE_TGA:
            log_info("Saving AsciiImg as tga...");
            res = stbi_write_tga(path_to_image, (int)img_w, (int)img_h, channels, pixels);
            log_info("Saved AsciiImg as tga");
            break;
        case FILE_BMP:
            log_info("Saving AsciiImg as bmp...");
            res = stbi_write_bmp(path_to_image, (int)img_w, (int)img_h, channels, pixels);
            log_info("Saved AsciiImg as bmp");
            break;
        case FILE_TXT:
        case FILE_NAF:
        default:
            log_error("Failed to save AsciiImg as image file");
            res = ASCII_IMG_ERR_FILE_SAVE;
            break;
    }

    free(pixels);

    return (!res || res == ASCII_IMG_ERR_FILE_SAVE) ? ASCII_IMG_ERR_FILE_SAVE : ASCII_IMG_OK;
}

static AsciiImgResult write_gray_jpg(const char *restrict path, int width, int height, unsigned char *restrict buffer){
    tjhandle handle = tjInitCompress();
    if (!handle) {
        return ASCII_IMG_ERR;
    }
    

#if defined(TJ_NUMINIT) // Api version > 3.1
    int result = tj3SaveImage8(handle, path, buffer, width, 0, height, TJPF_GRAY);
#else
    int result = tjSaveImage(path, buffer, width, 0, height, TJPF_GRAY, TJFLAG_FASTDCT);
#endif

    tjDestroy(handle);
    if (result == 0) {
        return ASCII_IMG_OK_TURBO_JPEG;
    }
    
    return ASCII_IMG_ERR_FILE_SAVE;
}

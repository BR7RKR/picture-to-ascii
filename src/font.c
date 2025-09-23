#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "font.h"
#include "font8x8_latin.h"
#include "font8x8_basic.h"

struct Font *Font_create(const unsigned char *restrict src, size_t symbols_count, size_t symbol_width, size_t symbol_height){
    struct Font *font = malloc(sizeof(*font));
    if (!font) {
        debug("Failed to allocate memory for font");
        return NULL;
    }

    font->map = malloc(symbols_count * sizeof(unsigned char *));
    if (!font->map) {
        free(font);
        debug("Failed to allocate memory for font map");
        return NULL;
    }

    font->symbol_width = symbol_width;
    font->symbol_height = symbol_height;
    font->symbols_count = symbols_count;

    size_t row_bytes = (symbol_width + 7) / 8;          // rounding to a larger value
    size_t symbol_bytes = row_bytes * symbol_height;

    for (size_t i = 0; i < symbols_count; i++) {
        font->map[i] = malloc(symbol_bytes);
        if (!font->map[i]) {
            debug("Failed to allocate memory for font maps' symbol bytes");
            Font_free(font);
            return NULL;
        }

        memcpy(font->map[i], src + i * symbol_bytes, symbol_bytes);
    }

    debug("Font was created successfully");
    return font;
}

void Font_free(struct Font *restrict font){
    if (!font) {
        return;
    }
    
    if (font->map) {
        for (size_t i = 0; i < font->symbols_count; i++) {
            if (font->map[i]) {
                free(font->map[i]);
            }
        }
        
        free(font->map);
    }
    
    font->symbols_count = 0;
    font->symbol_height = 0;
    font->symbol_width = 0;
}

struct Font *Font_create_font8x8_basic(void){
    return Font_create((const unsigned char*)font8x8_basic, 128, 8, 8);
}

struct Font *Font_create_font8x8_latin(void){
    const size_t control_count = 32;
    const size_t basic_count = 128;
    const size_t ext_count = 96;
    const size_t total_count = control_count + basic_count + ext_count;
    const size_t symbol_width = 8;
    const size_t symbol_height = 8;

    unsigned char *restrict temp = malloc(total_count * symbol_height * ((symbol_width + 7) / 8));
    if (!temp) {
        return NULL;
    }

    for (size_t i = 0; i < control_count; i++){
        memcpy(temp + i * symbol_height, font8x8_control[i], symbol_height);
    }

    for (size_t i = 0; i < basic_count; i++){
        memcpy(temp + (control_count + i) * symbol_height, font8x8_basic[i], symbol_height);
    }

    for (size_t i = 0; i < ext_count; i++){
        memcpy(temp + (control_count + basic_count + i) * symbol_height, font8x8_ext_latin[i], symbol_height);
    }

    struct Font *font = Font_create(temp, total_count, symbol_width, symbol_height);
    free(temp);

    return font;
}

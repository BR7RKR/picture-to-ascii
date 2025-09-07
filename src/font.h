#pragma once
#include <stdio.h>

struct Font{
    unsigned char **map;
    size_t symbols_count;
    size_t symbol_width;
    size_t symbol_height;
};

struct Font *Font_create(const unsigned char *src, size_t symbols_count, size_t symbol_width, size_t symbol_height);
void Font_free(struct Font *font);

struct Font *Font_create_font8x8_basic(void);
struct Font *Font_create_font8x8_latin(void);

#include "converter_cfg.h"
#include "global.h"

struct ConverterConfig ConverterConfig_create(const char *ascii_chars, size_t ascii_chars_size, float width_scale, float height_scale){
    struct ConverterConfig cfg = {0};
    
    if (!ascii_chars) {
        return cfg;
    }
    
    if (ascii_chars_size <= 0) {
        return cfg;
    }
    
    if (width_scale < 0 || is_equalf(width_scale, 0)) {
        return cfg;
    }
    
    if (height_scale < 0 || is_equalf(height_scale, 0)) {
        return cfg;
    }
    
    cfg.ascii_chars = ascii_chars;
    cfg.ascii_chars_size=ascii_chars_size;
    cfg.height_scale = height_scale;
    cfg.width_scale = width_scale;
    
    return cfg;
}

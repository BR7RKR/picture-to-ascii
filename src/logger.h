#pragma once
#include <stdio.h>

static inline void log_error(const char *message){
    printf("ERROR: %s\n", message);
}

static inline void log_info(const char *message){
    printf("INFO: %s\n", message);
}
static inline void log_warning(const char *message){
    printf("!WARNING!: %s\n", message);
}
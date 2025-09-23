#pragma once
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef RELEASE
#define log_error(M, ...) fprintf(stderr, "[ERROR]: " M "\n", ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO]: " M "\n", ##__VA_ARGS__)
#define log_warning(M, ...) fprintf(stderr, "[WARN]: " M "\n", ##__VA_ARGS__)
#define debug(M, ...)
#else
#define log_error(M, ...) fprintf(stderr, "[ERROR] (%s:%d [%s]) " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d [%s]) " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define log_warning(M, ...) fprintf(stderr, "[WARN] (%s:%d [%s]) " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d [%s]: " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#endif

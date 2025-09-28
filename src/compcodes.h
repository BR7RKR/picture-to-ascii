#pragma once

// Numbers here have no real meaning
// I was just messing aroud)
typedef enum {
    PTS_OK = 0,
    
    PTS_ERR_NOT_ENOUGH_ARGS = 1,
    PTS_ERR = -404,                 // Unknown error
    PTS_ERR_FLOAT_PARSE = -1,
    PTS_ERR_IMG_PATH = -3,          // Failed to read path to the image
    PTS_ERR_CFG_CREATION = 4,
    PTS_ERR_IMG_READ = -4,          // Failed to read the image
    PTS_ERR_CONVERT = -100,         // Failed to convert the img to ascii
    PTS_ERR_SAVE_TXT = -33,         // Failed to save ascii img as txt file
    PTS_ERR_NEGATIVE_ZERO = -331,   // Value is negative or zero
    PTS_ERR_UNKNOWN_FLAG = -7404
} CompCode;

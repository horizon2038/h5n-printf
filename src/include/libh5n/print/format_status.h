#ifndef LIBH5N_FORMAT_STATUS_H
#define LIBH5N_FORMAT_STATUS_H

#include <stdbool.h>

typedef struct
{
    int width;
    bool has_zero_pad;
    bool has_long_modifier;
    bool has_long_long_modifier;
} format_status;

#endif

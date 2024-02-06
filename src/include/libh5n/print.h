#ifndef H5N_PRINT_H
#define H5N_PRINT_H

#include <stdarg.h>

void libh5n_printf(const char *format, ...);
void libh5n_vsprintf(char *buffer, const char *format, va_list args);

void process_format(char **buffer, const char **format, va_list args);
void put_char(char **destination, const char source);

#endif

#ifndef LIBH5N_VSPRINTF_H
#define LIBH5N_VSPRINTF_H

#include <libh5n/print/format_status.h>

#include <stdarg.h>

void libh5n_vsprintf(char *buffer, const char *format, va_list args);

void process_format(char **buffer, const char **format, va_list args);
void put_char(char **destination, const char source);

#endif

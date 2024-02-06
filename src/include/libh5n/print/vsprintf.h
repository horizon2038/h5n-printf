#ifndef LIBH5N_VSPRINTF_H
#define LIBH5N_VSPRINTF_H

#include <libh5n/print/format_status.h>

#include <stdarg.h>

void libh5n_vsprintf(char *buffer, const char *format, va_list args);

void put_char(char **destination, const char source);
void process_format(char **buffer, const char **format, va_list args);
format_status process_format_flag(const char **format, va_list args);
void process_format_specifier(
    char **buffer,
    const char specifier,
    format_status *status,
    va_list args
);

#endif

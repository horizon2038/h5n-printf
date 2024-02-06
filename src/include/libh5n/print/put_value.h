#ifndef LIBH5N_PUT_VALUE_H
#define LIBH5N_PUT_VALUE_H

#include <libh5n/print/format_status.h>

void put_char(char **destination, const char source);
void put_string(char **destination, const char *source);
void put_int(char **destination, int value, format_status *status);

#endif

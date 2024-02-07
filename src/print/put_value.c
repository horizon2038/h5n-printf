#include <libh5n/print/put_value.h>
#include <stdio.h>
#include <stdint.h>

void put_char(char **destination, const char source)
{
    if (!(*destination))
    {
        return;
    }
    **destination = source;
    (*destination)++;
}

void put_string(char **destination, const char *source)
{
    while (*source != '\0')
    {
        put_char(destination, *source);
        source++;
    }
}

uintmax_t
    make_value_sign(char **destination, uintmax_t value, format_status *status)
{
    if (value < 0)
    {
        put_char(destination, '-');
        value -= value;
        --status->width;
    }
    return value;
}

void make_value_width(
    char **buffer,
    size_t buffer_size,
    uintmax_t value,
    format_status *status
)
{
    do
    {
        *(--(*buffer)) = '0' + (value % 10);
        value /= 10;
        --status->width;
    } while (value > 0);
}

void make_value_pad(char **destination, format_status *status)
{
    for (; status->width > 0; status->width--)
    {
        put_char(destination, status->has_zero_pad ? '0' : ' ');
    }
}

void put_int(char **destination, int value, format_status *status)
{
    if (value < 0)
    {
        put_char(destination, '-');
        value = -value; // reverse the number signs.
        --status->width;
    }

    // 32-bit value.
    // log((2^32) - 1) = 9.6239...
    // = 10.
    //
    char buffer[10];
    char *pointer = buffer + 10;

    do
    {
        *--pointer = '0' + (value % 10);
        value /= 10;
        --status->width;
    } while (value > 0);

    while (status->width-- > 0)
    {
        put_char(destination, status->has_zero_pad ? '0' : ' ');
    }

    while (pointer < buffer + 10)
    {
        put_char(destination, *pointer++);
    }
}

void put_int_ll(char **destination, long long value, int width, bool zero_pad)
{
    if (value < 0)
    {
        put_char(destination, '-');
        value = -value;
        --width;
    }

    char buffer[20];
    char *pointer = buffer + 20;

    do
    {
        *--pointer = '0' + (value % 10);
        value /= 10;
        --width;
    } while (value > 0);

    while (width-- > 0)
    {
        put_char(destination, zero_pad ? '0' : ' ');
    }

    while (pointer < buffer + 20)
    {
        put_char(destination, *pointer++);
    }
}

void put_uint(char **destination, unsigned int value, int width, bool zero_pad)
{
    char buffer[10];
    char *pointer = buffer + 10;

    do
    {
        *--pointer = '0' + (value % 10);
        value /= 10;
        --width;
    } while (value > 0);

    while (width-- > 0)
    {
        put_char(destination, zero_pad ? '0' : ' ');
    }

    while (pointer < buffer + 10)
    {
        put_char(destination, *pointer++);
    }
}

void put_uint_ll(
    char **destination,
    unsigned long long value,
    int width,
    bool zero_pad
)
{
    char buffer[20];
    char *pointer = buffer + 20;

    do
    {
        *--pointer = '0' + (value % 10);
        value /= 10;
        --width;
    } while (value > 0);

    while (width-- > 0)
    {
        put_char(destination, zero_pad ? '0' : ' ');
    }

    while (pointer < buffer + 20)
    {
        put_char(destination, *pointer++);
    }
}

void put_hex(
    char **destination,
    unsigned int value,
    int width,
    bool zero_pad,
    bool uppercase
)
{
    char buffer[8];
    char *pointer = buffer + 8;

    do
    {
        int digit = value % 16;
        *--pointer = (digit < 10) ? ('0' + digit) :
                                    ((uppercase ? 'A' : 'a') + digit - 10);
        value /= 16;
        --width;
    } while (value > 0);

    char pad_char = zero_pad ? '0' : ' ';

    while (width-- > 0)
    {
        put_char(destination, pad_char);
    }

    while (pointer < buffer + 8)
    {
        put_char(destination, *pointer++);
    }
}

void put_hex_ll(
    char **destination,
    unsigned long long value,
    int width,
    bool zero_pad,
    bool uppercase
)
{
    char buffer[16];
    char *pointer = buffer + 16;

    do
    {
        int digit = value % 16;
        *--pointer = (digit < 10) ? ('0' + digit) :
                                    ((uppercase ? 'A' : 'a') + digit - 10);
        value /= 16;
        --width;
    } while (value > 0);

    char pad_char = zero_pad ? '0' : ' ';

    while (width-- > 0)
    {
        put_char(destination, pad_char);
    }

    while (pointer < buffer + 16)
    {
        put_char(destination, *pointer++);
    }
}

void put_pointer(char **destination, const void *pointer)
{
    static const char *hex_digits = "0123456789abcdef";
    unsigned long value = (unsigned long)(pointer);

    put_char(destination, '0');
    put_char(destination, 'x');

    for (int i = (sizeof(pointer) * 8) - 4; i >= 0; i -= 4)
    {
        unsigned char nibble = (value >> i) & 0xf;
        put_char(destination, hex_digits[nibble]);
    }
}

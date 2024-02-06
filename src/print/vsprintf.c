#include <libh5n/print/vsprintf.h>

#include <libh5n/print/put_value.h>

#include <stdarg.h>
#include <stdio.h>

void libh5n_vsprintf(char *buffer, const char *format, va_list args)
{
    char *destination = buffer;

    for (const char *current_char = format; *current_char != '\0';
         current_char++)
    {
        if (*current_char == '%')
        {
            current_char++;
            process_format(&destination, &current_char, args);
        }
        else
        {
            put_char(&destination, *current_char);
        }

        /*
        printf(
            "current_buffer : %c\ncurrent_char : %c\n",
            *destination,
            *current_char
        );
        */
    }
    *destination = '\0';
}

void process_format(char **buffer, const char **format, va_list args)
{
    char current_char = **format;
    format_status status = process_format_flag(format, args);
    process_format_specifier(buffer, current_char, &status, args);
}

format_status process_format_flag(const char **format, va_list args)
{
    format_status status = { 0 };
    while (true)
    {
        if (**format == '0' && !status.width)
        {
            status.has_zero_pad = true;
            (*format)++;
        }
        else if (**format >= '1' && **format <= '9')
        {
            status.width = status.width * 10 + (**format - '0');
            (*format)++;
        }
        else if (**format == '0' && status.width)
        {
            status.width = status.width * 10;
            (*format)++;
        }
        else if (**format == 'l')
        {
            if (*(*format + 1) == 'l')
            {
                status.has_long_long_modifier = true;
                *format += 2;
            }
            else
            {
                status.has_long_modifier = true;
                (*format)++;
            }
        }
        else
        {
            break;
        }
    }
    return status;
}

void process_format_specifier(
    char **buffer,
    const char specifier,
    format_status *status,
    va_list args
)
{
    switch (specifier)
    {
        case 'c' :
            {
                char c = va_arg(args, int);
                put_char(buffer, c);
                break;
            }
        case 's' :
            {
                char *target_string = va_arg(args, char *);
                put_string(buffer, target_string);
                break;
            }
        case 'd' :
            {
                int target_value = va_arg(args, int);
                put_int(buffer, target_value, status);
                break;
            }

        default :
            {
                printf("unsupported format specifier: %c\n", specifier);
                break;
            }
    }
}

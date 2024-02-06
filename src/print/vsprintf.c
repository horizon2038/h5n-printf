#include <libh5n/print/vsprintf.h>

#include <stdarg.h>
#include <stdio.h>

void libh5n_vsprintf(char *buffer, const char *format, va_list args)
{
    printf("\n");
    printf("libh5n_vprintf\n");

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

        printf(
            "current_buffer : %c\ncurrent_char : %c\n",
            *destination,
            *current_char
        );
    }
    *destination = '\0';
}

void process_format(char **buffer, const char **format, va_list args)
{
    printf("process_format\n");
    char current_char = *(*format)++;

    switch (current_char)
    {
        case 'c' :
            {
                printf("current_char == c\n");
                put_char(buffer, va_arg(args, int));
                break;
            }
        case 's' :
            {
                char *target_string = va_arg(args, char *);
                for (const char *current_char = target_string;
                     *current_char != '0';
                     current_char++)
                {
                    put_char(buffer, *current_char);
                }
                break;
            }
        case 'd' :
            {
                break;
            }

        default :
            {
                printf("unsupported format specifier: %c\n", current_char);
                break;
            }
    }
}

void put_char(char **destination, const char source)
{
    if (!(*destination))
    {
        return;
    }
    **destination = source;
    (*destination)++;
}

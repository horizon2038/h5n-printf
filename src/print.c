#include <libh5n/print.h>

#include <stdio.h>

char buffer[100];

void libh5n_printf(const char *format, ...)
{
    printf("libh5n_printf\n");
    va_list args;
    va_start(args, format);
    libh5n_vsprintf(buffer, format, args);
    va_end(args);

    printf("%s\n", buffer);
    printf("\n");
}

void libh5n_vsprintf(char *buffer, const char *format, va_list args)
{
    printf("\n");
    printf("libh5n_vprintf\n");

    char *destination = buffer;

    for (const char *current_char = format; *current_char != '\0'; current_char++)
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

        printf("current_buffer : %c\ncurrent_char : %c\n", *destination, *current_char);
    }
    *destination = '\0';
}

void process_format(char **buffer, const char **format, va_list args)
{
    printf("process_format\n");
    char current_char = *(*format)++;
    if (current_char == 'c')
    {
        printf("current_char == c\n");
        put_char(buffer, va_arg(args, int));
        // *(*buffer++) = va_arg(args, int);
    }
    else if (current_char == 's')
    {
        char *target_string = va_arg(args, char*);
        for (const char *current_char = target_string; *current_char != '0'; current_char++)
        {
            put_char(buffer, *current_char);
        }
    }
    else
    {
        printf("Unsupported format specifier: %c\n", current_char);
    }


}

void put_char(char **destination, const char source)
{
    if(!(*destination))
    {
        return;
    }
    **destination = source;
    (*destination)++;
}

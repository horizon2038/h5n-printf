#include <libh5n/print.h>

#include <stdio.h>

// In the current version, values are written to a fixed-length string buffer
// for simplification. Therefore, the upper limit of the string is equal to the
// size of PRINT_BUFFER_MAX.
#define PRINT_BUFFER_MAX 100
char buffer[PRINT_BUFFER_MAX];

// Our printf delegates the processing to vsprintf.
// Therefore, it becomes a de facto wrapper.
void libh5n_printf(const char *format, ...)
{
    // Explanation of Variable Arguments in C
    // C allows you to define functions that take a variable number of
    // arguments, such as function(...).
    // Variable arguments are arguments that can be passed to a function in any
    // number when the function is called.
    // To access variable arguments, the following mechanisms are used:

    // **va_list**
    // A structure that stores the variable arguments.

    // **va_start(va_list ap, arg)**
    // A macro that initializes the processing of variable arguments.
    // - ap specifies a va_list type variable to store the variable arguments.
    // - arg specifies the argument that immediately precedes the variable
    // argument ... . This argument becomes the first element in the variable
    // argument list.

    // va_arg(va_list ap, type)
    // A macro that retrieves the next argument from ap.
    // - ap specifies a va_list type variable to store the variable arguments.
    // - type specifies the type of the argument to be retrieved.

    // va_end(va_list ap)
    // A macro that terminates the processing of variable arguments.

    // ap specifies a va_list type variable to store the variable arguments.
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

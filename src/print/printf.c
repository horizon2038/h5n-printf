#include <libh5n/print/printf.h>

#include <libh5n/print/vsprintf.h>

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
    //   argument ... . This argument becomes the first element in the variable
    //   argument list.

    // **va_arg(va_list ap, type)**
    // A macro that retrieves the next argument from ap.
    // - ap specifies a va_list type variable to store the variable arguments.
    // - type specifies the type of the argument to be retrieved.

    // va_end(va_list ap)
    // A macro that terminates the processing of variable arguments.
    // - ap specifies a va_list type variable to store the variable arguments.

    printf("libh5n_printf\n");
    va_list args;
    va_start(args, format);
    libh5n_vsprintf(buffer, format, args);
    va_end(args);

    printf("%s", buffer);
}

#include <libh5n/print.h>

#include <stdarg.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        printf("invalid argument!\n");
        return -1;
    }

    libh5n_printf(argv[1], argv[2]);
    return 0;
}

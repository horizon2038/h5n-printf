#include <libh5n/print/print.h>

#include <stdio.h>

int main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        printf("invalid argument!\n");
        return -1;
    }

    libh5n_printf(argv[1], argv[2]);
    libh5n_printf("value : %c\n", 'w');
    libh5n_printf("value : %s\n", "grenlagan");
    libh5n_printf("value : %d\n", 2038);
    libh5n_printf("value : %d\n", -2038);
    return 0;
}

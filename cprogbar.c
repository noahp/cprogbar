#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//! from https://stackoverflow.com/a/25934909
uint32_t baseTenDigits(uint32_t x) {
    static const unsigned char guess[33] = {
        0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
        9, 9, 9
    };
    static const uint32_t tenToThe[] = {
        1, 10, 100, 1000, 10000, 100000,
        1000000, 10000000, 100000000, 1000000000,
    };
    uint32_t digits = guess[x ? 32 - __builtin_clz(x) : 0];
    return digits + (x >= tenToThe[digits]);
}


size_t cprogbar(size_t current_offset, size_t new_offset, size_t max_offset) {



    printf("\r%zu.%0*zu", 4, 0, 4);
    return 0;
}

#include <unistd.h>
int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }

    unsigned long max_offset = strtoul(argv[1], NULL, 0);
    size_t progbar = 0;

    // for (size_t i = 0; i < max_offset; i++) {
    //     progbar = cprogbar(progbar, i, max_offset);
    //     usleep(100);
    // }

    printf("%zu\n", baseTenDigits(1));
    printf("%zu\n", baseTenDigits(10));
    printf("%zu\n", baseTenDigits(100));
    printf("%zu\n", baseTenDigits(1000));
    printf("%zu\n", baseTenDigits(10000));
    printf("%zu\n", baseTenDigits(100000));
    printf("%zu\n", baseTenDigits(1000000));
    printf("%zu\n", baseTenDigits(10000000));
    printf("%zu\n", baseTenDigits(100000000));
    printf("%zu\n", baseTenDigits(2567));

    return 0;
}

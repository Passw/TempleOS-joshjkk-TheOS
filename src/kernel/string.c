#include "include/string.h"
#include "include/stdint.h"

size_t strlen(char *str) {
    size_t i = 0;
    while (*str) {
        i++;
        str++;
    }
    if (i > 0)
        return i;
    else 
        return 0;
}

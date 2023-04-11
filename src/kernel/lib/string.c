#include "include/string.h"
#include "include/stdlib.h"
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

char *strcpy(char *dest, const char *src)
{
    char *original_dest = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return original_dest;
}

char *strdup(const char *src) {
    if (src == NULL)
        return NULL;

    char *dst = (char *)malloc(strlen((char *)src) + 1);
    if (dst == NULL)
        return NULL;

    strcpy(dst, src);
    return dst;
}

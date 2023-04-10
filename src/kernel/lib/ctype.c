#include "include/ctype.h"
#include "include/stdint.h"

int isalpha(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return TRUE;
    else
        return FALSE;
}

int isdigit(char c) {
    if (c >= '0' && c <= '9')
        return TRUE;
    else
        return FALSE;
}


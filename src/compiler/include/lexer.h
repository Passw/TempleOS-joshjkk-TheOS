#ifndef LEXER_H
#define LEXER_H

#include "../../kernel/lib/include/stdio.h"

typedef struct Lexer {
    char *src;
    size_t i;
    char c;
} lexer_t;

lexer_t *init_lexer(char *src);

#endif /* LEXER_H */

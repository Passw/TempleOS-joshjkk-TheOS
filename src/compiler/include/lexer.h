#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "../../kernel/lib/include/stdio.h"

typedef struct Lexer {
    char *src;
    size_t i;
    char c;
} lexer_t;

lexer_t *init_lexer(char *src);

token_t *lexer_next_token(lexer_t *lexer);

void lexer_lex(lexer_t *lexer);

#endif /* LEXER_H */

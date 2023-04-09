#include "include/lexer.h"
#include "../kernel/lib/include/stdio.h"
#include "../kernel/lib/include/stdlib.h"
#include "../kernel/lib/include/string.h"
#include "../kernel/lib/include/ctype.h"

lexer_t *init_lexer(char *src) {
    lexer_t *lexer = (lexer_t *)malloc(sizeof(lexer_t));
    lexer->src = src;
    lexer->i = 0;
    lexer->c = lexer->src[lexer->i];
    return lexer;
}

/*
void lexer_advance(lexer_t *lexer) {
    if (lexer->i < strlen(lexer->src) && lexer->c != '\0') {
        lexer->i++;
        lexer->c = lexer->src[lexer->i];
    }
}


token_t *lexer_advance_cur(lexer_t *lexer, int type) {
    char *value = (char *)malloc(2 * sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';
    lexer_advance(lexer);
    return init_token(value, type);
}

token_t *lexer_advance_with(lexer_t *lexer, token_t *token) {
    lexer_advance(lexer);
    return token;
}

void lexer_skip_white(lexer_t *lexer) {
    while (lexer->c == '\r' || lexer->c == '\n' || lexer->c == '\t' || lexer->c == ' ')
        lexer_advance(lexer);
}

token_t *lexer_lex_id(lexer_t *lexer) {
    size_t value_size = 0;
    char *value = NULL;
    
    while (isalpha(lexer->c)) {
        value = (char *)realloc(value, (value_size + 1) * sizeof(char));
        value[value_size++] = lexer->c;
        lexer_advance(lexer);
    }
    
    value = (char *)realloc(value, (value_size + 1) * sizeof(char));
    value[value_size] = '\0';
    return init_token(value, TOKEN_ID);
}

token_t *lexer_lex_num(lexer_t *lexer) {
    size_t value_size = 0;
    char *value = NULL;
    
    while (isdigit(lexer->c)) {
        value = (char *)realloc(value, (value_size + 1) * sizeof(char));
        value[value_size++] = lexer->c;
        lexer_advance(lexer);
    }
    
    value = (char *)realloc(value, (value_size + 1) * sizeof(char));
    value[value_size] = '\0';
    return init_token(value, TOKEN_INT);
}

char lexer_peek(lexer_t *lex, size_t offset) {
    return lex->src[MIN(lex->i + offset, strlen(lex->src))];
}

token_t *lexer_next_tok(lexer_t *lexer) {
    while (lexer->c != '\0') {
        lexer_skip_white(lexer);

        if (isalpha(lexer->c))
            return lexer_lex_id(lexer);

        if (isdigit(lexer->c))
            return lexer_lex_num(lexer);

        switch (lexer->c) {
            case '(': return lexer_advance_cur(lexer, TOKEN_LPAREN);
            case ')': return lexer_advance_cur(lexer, TOKEN_RPAREN);
            case ',': return lexer_advance_cur(lexer, TOKEN_COMMA);
            case '*': return lexer_advance_cur(lexer, TOKEN_STAR);
            case '{': return lexer_advance_cur(lexer, TOKEN_LBRACE);
            case '}': return lexer_advance_cur(lexer, TOKEN_RBRACE);
            case '=':
                if (lexer_peek(lexer, 1) == '>')
                    return lexer_advance_with(lex, lexer_advance_with(lex, init_token("=>", TOKEN_ARROW)));
                return lexer_advance_cur(lex, TOKEN_EQUALS);
            case ';': return lexer_advance_cur(lex, TOKEN_SEMICOLON);
            case '\0': goto eof;
            //default: fprintf(stderr, "[Lexer]: Unexpected token '%c'\n", lex->c); exit(1);
        }
    }
eof:
    return init_token(0, TOK_EOF);
}

void lexer_lex(lexer_t *lexer) {
    token_t *token;
    while ((token = lexer_next_token(lexer))->type != TOKEN_EOF) {
        char *token_str = token_to_str(token);
        printf("%s\n", token_str);
        free(token_str);
    }
    free(token);
}
*/

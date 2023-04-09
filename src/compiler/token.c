#include "include/token.h"
#include "../kernel/lib/include/stdio.h"
#include "../kernel/lib/include/stdlib.h"
#include "../kernel/lib/include/string.h"

token_t *init_token(char *value, int type) {
    token_t *token = (token_t *)malloc(sizeof(token_t));
    token->value = value;
    token->type = type;
    return token;
}

char *token_type_to_str(int type) {
    switch (type) {
        case TOKEN_ID: return "TOKEN_ID";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_STAR: return "TOKEN_STAR";
        case TOKEN_ARROW: return "TOKEN_ARROW";
        case TOKEN_LBRACE: return "TOKEN_LBRACE";
        case TOKEN_RBRACE: return "TOKEN_RBRACE";
        case TOKEN_EQUALS: return "TOKEN_EQUALS";
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        default: return "NOT_STRINGABLE";
    }
}

char *tok_to_str(token_t *token) {
    const char *type_str = token_type_to_str(token->type);
    const char *template = "<type = '%s', int_type = '%d', value = '%s'>";
    
    char *str = (char *)malloc((strlen((char *)type_str) + strlen((char *)template) + 8) * sizeof(char));
    sprintf(str, template, type_str, token->type, token->value);
    return str;
}

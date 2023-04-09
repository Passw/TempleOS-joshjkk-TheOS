#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token {
    char *value;
    enum {
        TOKEN_ID,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_COMMA,
        TOKEN_STAR,
        TOKEN_ARROW,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_EQUALS,
        TOKEN_INT,
        TOKEN_SEMICOLON,
        TOKEN_EOF
    } type;
} token_t;

token_t *init_token(char *value, int type);

char *token_type_to_str(int type);

char *token_to_str(token_t *token);

#endif /* TOKEN_H */

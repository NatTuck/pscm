#ifndef PSCM_TOKENIZE_H
#define PSCM_TOKENIZE_H

#include <stdint.h>

typedef struct ps_source {
    char*   path;
    char*   text;
    int64_t pos;
} ps_source;

typedef enum token_type {
    NULL_TOK,
    BAD_TOK,
    NAME_TOK,
    STRING_TOK,
    NUMBER_TOK,
    LPAREN_TOK,
    RPAREN_TOK,
    RSQUARE_TOK,
    LSQUARE_TOK,
    RCURLY_TOK,
    LCURLY_TOK,
    QUOTE_TOK
} token_type;

typedef struct ps_token {
    ps_source* source;
    int64_t    offset;
    char*      text;
    token_type type;
} ps_token;

ps_source* source_from_string(const char* path, const char* text);
ps_source* source_from_path(const char* path);

ps_token*  next_token(ps_source* code);


#endif

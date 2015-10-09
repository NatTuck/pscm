#ifndef PSCM_READER_H
#define PSCM_READER_H

#include "mem.h"

typedef struct ps_source {
    PSCM_REFCOUNT
    char* path;
    char* text;
    int   pos;
} ps_source;

typedef enum tok_type {
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
} tok_type;

typedef struct ps_token {
    PSCM_REFCOUNT
    ps_source* source;
    tok_type   type;
    char*      text;
} ps_token;

ps_source* open_string(const char* text);
ps_source* open_source(const char* path);
ps_token* next_token(ps_source*);

#endif

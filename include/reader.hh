#ifndef PSCM_READER_H
#define PSCM_READER_H

#include "mem.hh"
#include "vals.hh"

typedef struct ps_source {
    ps_val val;
    char* path;
    char* text;
    int   pos;
} ps_source;

typedef enum tok_type {
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
} tok_type;

typedef struct ps_token {
    ps_val val;
    ps_source* source;
    int        s_pos;
    tok_type   type;
    char*      text;
} ps_token;

ps_source* source_from_string(const char* text);
ps_source* source_from_path(const char* path);

ps_token*  next_token(ps_source* code);

#endif

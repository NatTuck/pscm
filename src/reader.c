
#include <bsd/string.h>
#include <ctype.h>

#include "mem.h"
#include "reader.h"
#include "io.h"

ps_source*
source_from_string(const char* text)
{
    ps_source* code = ALLOC(ps_source);
    code->path = pscm_strdup("[string]");
    code->text = pscm_strdup(text);
    return code;
}

ps_source*
source_from_path(const char* path)
{
    ps_source* code = ALLOC(ps_source);
    code->path = pscm_strdup(path);
    code->text = read_whole_file(path);
    return code;
}

void
retain_source(ps_source* code)
{
    pscm_retain(code);
}

void
release_source(ps_source* code)
{
    if (pscm_release(code)) {
        pscm_free(code->path);
        pscm_free(code->text);
        pscm_free(code);
    }
}

static
int
is_name_char(char cc)
{
    return !( isspace(cc)
           || cc == '(' || cc == ')'
           || cc == '[' || cc == ']'
           || cc == '{' || cc == '}'
           || cc == '#' || cc == '|'
           || cc == ',' || cc == '`'
           || cc == ';' || cc == '"'
           || cc == '\'' );
}

static
char*
read_number(const char* text)
{
    int size = 0;
    while (isdigit(*(text + size)) || *(text + size) == '.') {
        size += 1;
    }

    char* tt = pscm_malloc(size + 1);
    strlcpy(tt, text, size + 1);
    return tt;
}

static
char*
read_name(const char* text)
{
    int size = 0;
    while (is_name_char(*(text + size))) {
        size += 1;
    }
    
    char* tt = pscm_malloc(size + 1);
    strlcpy(tt, text, size + 1);
    return tt;
}

static
char*
read_string(const char* text)
{
    int nn = strlen(text);
    char* tmp = pscm_malloc(nn + 1);
    memset(tmp, 0, nn + 1);

    tmp[0] = '"';
    text++;

    for (int ii = 1; ii < nn; ++ii) {
        hard_assert(*text != 0, "null in string literal");

        if (*text == '\\') {
            tmp[ii] = *text;
            text++; ii++;
            tmp[ii] = *text;
            text++;
            continue;
        }

        if (*text == '"') {
            tmp[ii] = '"';
            break;
        }

        tmp[ii] = *text;
        text++;
    }

    char* ss = pscm_strdup(tmp);
    pscm_free(tmp);
    return ss;
}

ps_token*
next_token(ps_source* code)
{
    while (isspace(*(code->text + code->pos))) {
        code->pos += 1;
    }

    char* text = code->text + code->pos;

    if (text[0] == 0) {
        return 0;
    }

    ps_token* tok = ALLOC(ps_token);
    tok->type   = BAD_TOK;
    tok->source = code;
    tok->s_pos  = code->pos;
    retain_source(code);

    if (text[0] == '(') {
        tok->type = LPAREN_TOK;
        tok->text = pscm_strdup("(");
    }

    if (text[0] == ')') {
        tok->type = RPAREN_TOK;
        tok->text = pscm_strdup(")");
    }

    if (text[0] == '\'') {
        tok->type = QUOTE_TOK;
        tok->text = pscm_strdup("'");
    }

    if (text[0] == '"') {
        tok->type = STRING_TOK;
        tok->text = read_string(text);
    }

    if (isdigit(text[0])) {
        tok->type = NUMBER_TOK;
        tok->text = read_number(text);
    }
    else if (is_name_char(text[0])) {
        tok->type = NAME_TOK;
        tok->text = read_name(text);
    }

    hard_assert(tok->type != BAD_TOK, "next_token is BAD_TOK");

    code->pos += strlen(tok->text);
    return tok;
}

void
retain_token(ps_token* tok)
{
    pscm_retain(tok);
}

void
release_token(ps_token* tok)
{
    if (pscm_release(tok)) {
        release_source(tok->source);
        pscm_free(tok->text);
        pscm_free(tok);
    }
}




#include <stdlib.h>

#include "mem.h"
#include "errors.h"
#include "io.h"
#include "tokenize.h"
#include "parse.h"
#include "lists.h"

ps_v*
parse_string(ps_token* tok)
{
    return make_ps_string(tok->text);
}

ps_v*
parse_number(ps_token* tok)
{
    return make_ps_int(atoi(tok->text));
}

ps_v*
parse_seq(ps_source* code, token_type term)
{
    ps_token* tok;
    ps_v* seq = make_ps_nil();
    ps_v* rseq;

    while ((tok = next_token(code))) {
        ps_v* vv;

        switch (tok->type) {
            case NAME_TOK:
                vv = make_ps_symbol(tok->text);
                break;
            case STRING_TOK:
                vv = parse_string(tok);
                break;
            case NUMBER_TOK:
                vv = parse_number(tok);
                break;
            case LPAREN_TOK:
                vv = parse_seq(code, RPAREN_TOK);
                break;
            case RPAREN_TOK:
                hard_assert(term == RPAREN_TOK, "unexpected ')'");
                release_token(tok);
                goto done;
            default:
                hard_assert(0, "unknown token");
        }

        seq = make_ps_cons(vv, seq);
        release_token(tok);
    } 

    hard_assert(term == NULL_TOK, "missing ')'");
done:
    rseq = reverse_list(seq);
    pscm_release(seq);
    return rseq;
}

ps_v*
parse(ps_source* code)
{
    return parse_seq(code, NULL_TOK);
}


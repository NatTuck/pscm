
#include <stdio.h>

#include "types.h"
#include "mem.h"
#include "lists.h"
#include "errors.h"
#include "eval.h"

ps_v* 
eval(ps_v* env, ps_v *code)
{
    if (is_ps_cons(code)) {
        ps_v* ev_code = map_eval(env, code);
        ps_cons* pair = (ps_cons*) ev_code;

        if (is_ps_func(pair->car)) {
            return apply(env, pair->car, pair->cdr);
        }

        if (is_ps_native(pair->car)) {
            return apply_native(env, pair->car, pair->cdr);
        }

        fprintf(stderr, "Tried to run a '%s'.\n", pair->car->type->name);
        fatal_error("That's not executable.");
    }

    if (is_ps_symbol(code)) {
        ps_v* val = plist_get(env, code);
        if (is_ps_nil(val)) {
            fprintf(stderr, "Unknown name: %s\n", to_c_str(code));
            fatal_error("giving up");
        }
        return val;
    }

    return code;
}

ps_v*
map_eval(ps_v* env, ps_v* code)
{
    if (is_ps_nil(code)) {
        return code;
    }

    hard_assert(is_ps_cons(code), "should be a list");
    ps_cons* pair = (ps_cons*) code;

    ps_v* ev_car = eval(env, pair->car);
    ps_v* ev_cdr = map_eval(env, pair->cdr);

    return make_ps_cons(ev_car, ev_cdr);
}

ps_v*
apply(ps_v* env, ps_v* func, ps_v* args) {
    //ps_func* fn = (ps_func*) func;
    return make_ps_int(42);
}

ps_v*
apply_native(ps_v* env, ps_v* func, ps_v* args)
{
    ps_native* nfn = (ps_native*) func;
    return (nfn->code)(args);
}


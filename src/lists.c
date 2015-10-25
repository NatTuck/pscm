
#include "errors.h"
#include "mem.h"
#include "types.h"
#include "lists.h"

int
list_empty(ps_v* xs)
{
    return xs->type == &PS_NIL_TYPE;
}

static
ps_v*
reverse_list2(ps_v* xs, ps_v* ys)
{
    if (list_empty(xs)) {
        return ys;
    }

    hard_assert(xs->type == &PS_CONS_TYPE, "not a list");
    ps_cons* pair = (ps_cons*) xs;
    ps_v*    car  = pair->car;
    ps_v*    cdr  = pair->cdr;

    return reverse_list2(cdr, make_ps_cons(car, ys));
}

ps_v*
reverse_list(ps_v* xs)
{
    return reverse_list2(xs, make_ps_nil());
}

ps_v*
list_ref_c(ps_v* xs, int64_t ii)
{
    hard_assert(ii >= 0, "negative index for list_ref?");

    if (list_empty(xs)) {
        return 0;
    }
        
    hard_assert(xs->type == &PS_CONS_TYPE, "not a list");
    ps_cons* pair = (ps_cons*)xs;

    if (ii == 0) {
        return pair->car;
    }
    else {
        return list_ref_c(pair->cdr, ii - 1);
    }
}

ps_v*
plist_put(ps_v* xs, ps_v* kk, ps_v* vv)
{
    ps_v* ent = make_ps_cons(kk, make_ps_cons(vv, make_ps_nil()));
    return make_ps_cons(ent, xs);
}

ps_v*
plist_get(ps_v* xs, ps_v* kk)
{
    if (list_empty(xs)) {
        return make_ps_nil();
    }

    hard_assert(xs->type == &PS_CONS_TYPE, "not a list");
   
    ps_cons* pair = (ps_cons*)xs;
    ps_v* lk = list_ref_c(pair->car, 0);
    ps_v* vv = list_ref_c(pair->car, 1);
    
    if (pscm_equal(lk, kk)) {
        return vv;
    }
    else {
        return plist_get(pair->cdr, kk);
    }
}


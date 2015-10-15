
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

    ps_cons* pair = (ps_cons*) xs;
    ps_v*    car  = pair->car;
    ps_v*    cdr  = pair->cdr;

    return reverse_list2(cdr, make_ps_cons(pscm_clone(car), ys));
}

ps_v*
reverse_list(ps_v* xs)
{
    return reverse_list2(xs, make_ps_nil());
}



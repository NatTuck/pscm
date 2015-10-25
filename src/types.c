
#include "mem.h"
#include "errors.h"
#include "types.h"

char*
to_c_str(ps_v* vv)
{
    if (is_ps_string(vv) || is_ps_symbol(vv)) {
        ps_string* ss = (ps_string*) vv;
        return pscm_strdup(ss->text);
    }
    else {
        hard_assert(0, "not a string");
        return 0;
    }
}

int64_t
to_c_int(ps_v* vv)
{
    if (vv->type == &PS_INT_TYPE) {
        ps_int* nn = (ps_int*) vv;
        return nn->num;
    }
    else {
        hard_assert(0, "not an integer");
        return -1;
    }
}

int
pscm_equal(ps_v* x, ps_v* y)
{
    if (x->type != y->type) {
        return 0;
    }

    return x->type->equal(x, y);
}

int
is_ps_list(ps_v* xs)
{
    return is_ps_cons(xs) || is_ps_nil(xs);
}


#include "mem.h"
#include "errors.h"
#include "types.h"

int
is_ps_list(ps_v* xs)
{
    return is_ps_cons(xs) || is_ps_nil(xs);
}

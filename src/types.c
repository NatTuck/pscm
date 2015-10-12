
#include "mem.h"
#include "io.h"
#include "types.h"

char*
to_c_str(ps_v* vv)
{
    if (vv->type == &PS_STRING_TYPE) {
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

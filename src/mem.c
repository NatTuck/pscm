#include "mem.h"

void*
pscm_alloc_rc(size_t sz)
{
    rc_obj* thing = (rc_obj*) malloc(sz);
    thing->refs = 1;
    return (void*) thing;
}

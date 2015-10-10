#include <string.h>

#include "mem.h"

void*
pscm_alloc_rc(size_t sz)
{
    rc_obj* thing = (rc_obj*) malloc(sz);
    memset(thing, 0, sz);
    thing->refs = 1;
    return (void*) thing;
}

void 
pscm_retain_rc(void* thing_vp)
{
    rc_obj* thing = (rc_obj*) thing_vp;
    thing->refs += 1;
}

int
pscm_release_rc(void* thing_vp)
{
    rc_obj* thing = (rc_obj*) thing_vp;
    thing->refs -= 1;

    return thing->refs == 0;
}

char*
pscm_strdup(const char* aa)
{
    char* bb = pscm_malloc(strlen(aa) + 1);
    strcpy(bb, aa);
    return bb;
}

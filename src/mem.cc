#include <string.h>

#include "mem.hh"

void*
pscm_malloc(size_t sz)
{
#ifdef REFCOUNT
    return malloc(sz);
#else
    return GC_malloc_atomic(sz);
#endif
}

char*
pscm_strdup(const char* aa)
{
    char* bb = (char*) pscm_malloc(strlen(aa) + 1);
    strcpy(bb, aa);
    return bb;
}


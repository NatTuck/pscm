#ifndef PSCM_MEM_HH
#define PSCM_MEM_HH

#ifndef REFCOUNT
#include <gc/gc.h>
#endif

#include <stdlib.h>
#include <string.h>

#include "types.h"

inline static
void* 
pscm_malloc(size_t sz)
{
#ifdef REFCOUNT
    return calloc(1, sz);
#else
    return GC_malloc_atomic(sz);
#endif
}

inline static
void
pscm_free(void* pp)
{
#ifdef REFCOUNT
    free(pp);
#endif
}

inline static
char* 
pscm_strdup(const char* ss)
{
    size_t nn = strlen(ss);
    char*  dd = pscm_malloc(nn + 2);
    strcpy(dd, ss);
    return dd;
}

inline static
void 
pscm_retain(ps_v* vv)
{
#ifdef REFCOUNT
    vv->refs += 1;
#endif
}

inline static
void
pscm_release(ps_v* vv)
{
#ifdef REFCOUNT    
    vv->refs -= 1;
    if (vv->refs == 0) {
        vv->type->cleanup(vv);
    }
#endif
}

inline static
ps_v*
pscm_clone(ps_v* vv)
{
    return vv->type->clone(vv);
}

#endif

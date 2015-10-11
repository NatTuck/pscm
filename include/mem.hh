#ifndef PSCM_MEM_HH
#define PSCM_MEM_HH

/*
 * pscm_alloc  - Allocate an object w/ internal refs that will be refcounted.
 * pscm_malloc - Allocate a chunk of bytes that will be freed.
 */

#include <stdint.h>
#include <stdlib.h>

#ifndef REFCOUNT
#include <gc/gc.h>
#endif

#include "vals.hh"

void* pscm_malloc(size_t);
char* pscm_strdup(const char*);

template <typename T>
int64_t
pscm_type()
{
    return 0;
}


template <typename T>
T*
pscm_alloc()
{
#ifdef REFCOUNT
    ps_val* val = (ps_val*) malloc(sizeof(T));
    val->refcount = 1;
    val->type = pscm_type<T>();
#else
    ps_val* val = (ps_val*) GC_malloc(sizeof(T));
    val->type = pscm_type<T>();
    return (T*) val;
#endif
}

template <typename T>
void
pscm_free(T* vv)
{
#ifdef REFCOUNT
    free(vv);
#endif
}

template <typename T>
void
pscm_retain(T* vv)
{
#if REFCOUNT
    vv->val.refcount += 1;
#endif
}

template <typename T>
void
pscm_release(T* vv)
{
#if REFCOUNT    
    vv->val.refcount -= 1;
    if (vv->val.refcount == 0) {
        pscm_cleanup(vv);
        pscm_free(vv);
    }
#endif
}

#endif

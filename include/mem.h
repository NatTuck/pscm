#ifndef PSCM_MEM_H
#define PSCM_MEM_H

#ifdef USE_GC

/* Use libgc for memory management */
#include <gc/gc.h>

#define pscm_alloc GC_malloc
#define pscm_release(x)
#define pscm_retain(x)

#define PSCM_REFCOUNT

#else // not USE_GC

/* Use refcounts for memory management */
#define pscm_alloc pscm_alloc_real(x)
#define pscm_release(x) pscm_release_real(x)
#define pscm_retain(x) pscm_retain_real(x)

#define PSCM_REFCOUNT \
    int64_t refs;

#endif

#define ALLOC(type) ((type*)pscm_alloc(sizeof(type)))
void pscm_alloc_real(size_t);
void pscm_release_real(void*);
void pscm_retain_real(void*);

#endif

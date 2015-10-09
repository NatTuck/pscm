#ifndef PSCM_MEM_H
#define PSCM_MEM_H

/*
 * pscm_alloc  - Allocate an object w/ internal refs that will be refcounted.
 * pscm_malloc - Allocate a chunk of bytes that will be freed.
 */

#ifdef USE_GC

/* Use libgc for memory management */
#include <gc/gc.h>

#define pscm_alloc(x) GC_malloc(x)
#define pscm_malloc(x) GC_malloc_atomic(x)
#define pscm_free(x) GC_free(x)

#define PSCM_REFCOUNT

#else

/* Use refcounts for memory management */
#include <stdlib.h>

#define pscm_alloc(x) pscm_alloc_rc(x)
#define pscm_malloc(x) malloc(x)
#define pscm_free(x) free(x)

#define PSCM_REFCOUNT \
    int64_t refs;

#endif

#define ALLOC(type) pscm_alloc(sizeof(type))

typedef struct rc_obj {
  int64_t refs;
} rc_obj;

void* pscm_alloc_rc(size_t);

#endif

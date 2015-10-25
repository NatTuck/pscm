#ifndef PSCM_MEM_HH
#define PSCM_MEM_HH

#include <gc/gc.h>
#include <string.h>

inline static
void* 
pscm_malloc(size_t sz)
{
    return GC_malloc_atomic(sz);
}

inline static
char* 
pscm_strdup(const char* ss)
{
    size_t nn = strlen(ss);
    char*  dd = pscm_malloc(nn + 1);
    strcpy(dd, ss);
    return dd;
}

#endif

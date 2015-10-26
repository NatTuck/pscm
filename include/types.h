#ifndef PSCM_TYPES_H
#define PSCM_TYPES_H

struct ps_v;

typedef struct ps_type {
    const char* name;
    void (*cleanup)(struct ps_v*);
    struct ps_v* (*clone)(struct ps_v*);
    char* (*show)(struct ps_v*);
    int   (*equal)(struct ps_v*, struct ps_v*);
} ps_type;

typedef struct ps_v* (*native_func)(struct ps_v*);

#include "gen/types.h"

int     is_ps_list(ps_v* xs);

inline static
int
pscm_equal(ps_v* xx, ps_v* yy)
{
    if (xx->type != yy->type) {
        return 0;
    } 
    else {
        return xx->type->equal(xx, yy);
    }
}

inline static
char*
pscm_show(ps_v* vv)
{
    return vv->type->show(vv);
}

#endif

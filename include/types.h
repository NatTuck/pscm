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

char*   to_c_str(ps_v* vv);
int64_t to_c_int(ps_v* vv);
int     pscm_equal(ps_v* x, ps_v* y);
int     is_ps_list(ps_v* xs);

#endif

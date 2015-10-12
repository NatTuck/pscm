#ifndef PSCM_TYPE_H
#define PSCM_TYPE_H

struct ps_v;

typedef struct ps_type {
    const char* name;
    void (*cleanup)(struct ps_v*);
    struct ps_v* (*clone)(struct ps_v*);
    void (*to_s)(struct ps_v*);
} ps_type;

#include "gen/types.h"

char*   to_c_str(ps_v* vv);
int64_t to_c_int(ps_v* vv);

#endif

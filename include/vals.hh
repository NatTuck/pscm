#ifndef PSCM_VALS_H
#define PSCM_VALS_H

#include <cstdint>

struct ps_val {
#ifdef REFCOUNT
    int64_t refs;
#endif
    int64_t type;
};

struct ps_symbol {
    ps_val val;
    char* text;
};

struct ps_string {
    ps_val val;
    char* text;
};

struct ps_int {
    ps_val val;
    int64_t num;
};

struct ps_float {
    ps_val val;
    double num;
};

struct ps_cons {
    ps_val val;
    ps_val* car;
    ps_val* cdr;
};

#endif

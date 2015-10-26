#ifndef PSCM_LISTS_H
#define PSCM_LISTS_H

#include "types.h"

int   list_empty(ps_v* xs);
int   list_length(ps_v* xs);
ps_v* reverse_list(ps_v* xs);
ps_v* list_ref_c(ps_v* xs, int64_t ii);

ps_v* plist_put(ps_v* xs, ps_v* kk, ps_v* vv);
ps_v* plist_get(ps_v* xs, ps_v* kk);

#endif

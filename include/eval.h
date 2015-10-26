#ifndef PSCM_EVAL_H
#define PSCM_EVAL_H

#include "types.h"

ps_v* eval(ps_v* env, ps_v* code);
ps_v* map_eval(ps_v* env, ps_v* code);
ps_v* apply(ps_v* env, ps_v* func, ps_v* args);
ps_v* apply_native(ps_v* env, ps_v* func, ps_v* args);
ps_v* eval_special(ps_v* env, ps_v* name, ps_v* args);
ps_v* eval_if(ps_v* env, ps_v* args);

#endif

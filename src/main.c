
#include <stdlib.h>
#include <stdio.h>

#include "tokenize.h"
#include "parse.h"
#include "mem.h"
#include "types.h"
#include "lists.h"
#include "eval.h"
#include "builtins.h"
#include "io.h"

int
main(int argc, char* argv[])
{
    pscm_init_types();
    ps_v* env = initial_env();

    //printf("%s\n", pscm_show(env));

    while(1) {
        char* line = pscm_readline("pscm> ");
        if (line == 0) {
            printf("\n");
            break;
        }

        ps_source* code = source_from_string("[test]", line);
        ps_v* vv = parse(code);

        ps_v* ii = vv;
        while (!list_empty(ii)) {
            ps_cons* cc = (ps_cons*) ii;

            ps_v* rv = eval(env, cc->car);
            char* text = pscm_show(rv);
            printf("%s\n", text);

            ii = cc->cdr;
        } 
    }

    return 0;
}


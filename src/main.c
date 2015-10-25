
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tokenize.h"
#include "parse.h"
#include "mem.h"
#include "types.h"
#include "lists.h"
#include "eval.h"

int
main(int argc, char* argv[])
{
    pscm_init_types();
    ps_v* env = make_ps_nil();

    while(1) {
        char* line = readline("pscm> ");
        if (line == 0) {
            printf("\n");
            break;
        }
        add_history(line);

        ps_source* code = source_from_string("[test]", line);
        free(line);

        ps_v* vv = parse(code);
        release_source(code);

        ps_v* ii = vv;
        while (!list_empty(ii)) {
            ps_cons* cc = (ps_cons*) ii;

            ps_v* rv = eval(env, cc->car);
            char* text = pscm_show(rv);
            printf("%s\n", text);
            pscm_free(text);
            pscm_release(rv);

            ii = cc->cdr;
        } 

        pscm_release(vv);
    }

    pscm_release(env);

    return 0;
}


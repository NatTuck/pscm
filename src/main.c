
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tokenize.h"
#include "parse.h"
#include "mem.h"
#include "types.h"
#include "lists.h"

int
main(int argc, char* argv[])
{
    pscm_init_types();

    while(1) {
        char* line = readline("pscm> ");
        if (line == 0) {
            printf("\n");
            break;
        }

        ps_source* code = source_from_string("[test]", line);
        free(line);

        ps_v* vv = parse(code);
        release_source(code);

        ps_v* ii = vv;
        while (!list_empty(ii)) {
            ps_cons* cc = (ps_cons*) ii;

            char* text = pscm_show(cc->car);
            printf("%s\n", text);
            pscm_free(text);
            
            ii = cc->cdr;
        } 

        pscm_release(vv);
    }

    return 0;
}



#include <alloca.h>
#include <stdio.h>

#include "tokenize.h"
#include "parse.h"
#include "mem.h"
#include "types.h"

int
main(int argc, char* argv[])
{
    pscm_init_types();

    char* line = (char*) alloca(100);

    while(1) {
        char* rv = fgets(line, 100, stdin);
        if (rv == 0) {
            break;
        }

        ps_source* code = source_from_string("[test]", line);
        ps_v* vv = parse(code);
        release_source(code);

        char* text = pscm_show(vv);
        printf("got:\n%s\n", text);
        free(text);

        pscm_release(vv);
    }

    return 0;
}



#include <alloca.h>
#include <stdio.h>

#include "reader.hh"

void
test_tokenize(const char* text)
{
    ps_source* code = source_from_string(text);
    ps_token* tok;

    while ((tok = next_token(code))) {
        printf("Token: [%s]\n", tok->text);
        pscm_release(tok);
    }

    printf("done\n");
    pscm_release(code);
}

int
main(int argc, char* argv[])
{
    char* line = (char*) alloca(100);

    while(1) {
        char* rv = fgets(line, 100, stdin);
        if (rv == 0) {
            break;
        }

        test_tokenize(line);
    }

    return 0;
}

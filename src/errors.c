
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "mem.h"
#include "gen/types.h"

void
assert_perror(int cond, const char* text)
{
    if (cond) {
        return;
    }

    perror(text);
    exit(1);
}

void
fatal_error(const char* text)
{
    fprintf(stderr, "fatal error: %s\n", text);
    exit(2);
}

void
hard_assert(int cond, const char* text)
{
    if (cond) {
        return;
    }

    fprintf(stderr, "failed hard assert\n");
    fatal_error(text);
}

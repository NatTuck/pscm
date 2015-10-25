
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "mem.h"
#include "types.h"

void
assert_perror_real(int cond, const char* text, const char* file, int line)
{
    if (cond) {
        return;
    }

    fprintf(stderr, "At %s:%d\n", file, line);
    perror(text);
    abort();
}

void
fatal_error_real(const char* text, const char* file, int line)
{
    fprintf(stderr, "At %s:%d\n", file, line);
    fprintf(stderr, "fatal error: %s\n", text);
    abort();
}

void
hard_assert_real(int cond, const char* text, const char* file, int line)
{
    if (cond) {
        return;
    }

    fprintf(stderr, "failed hard assert\n");
    fatal_error_real(text, file, line);
}


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "mem.h"

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
hard_assert(int cond, const char* text)
{
    if (cond) {
        return;
    }

    fprintf(stderr, "%s: failed hard_assert\n", text);
    exit(2);
}

char*
read_whole_file(const char* path)
{
    int rv = 0;
    struct stat info;
    
    rv = stat(path, &info);
    assert_perror(rv == 0, "stat");

    char* buff = (char*) calloc(1, info.st_size);
    FILE* ff = fopen(path, "r");
    assert_perror(ff != 0, "fopen");

    int nn = fread(buff, info.st_size, 1, ff);
    assert_perror(nn == info.st_size, "fread");

    rv = fclose(ff);
    assert_perror(rv == 0, "fclose");

    return buff;
}

char*
pscm_sprintf(const char* fmt, ...)
{
    va_list as1;
    va_list as2;

    va_start(as1, fmt);
    va_copy(as2, as1);

    int nn = vsnprintf(0, 0, fmt, as1);
    char* ss = pscm_malloc(nn + 1);
    vsnprintf(ss, nn + 1, fmt, as2);

    va_end(as2);
    va_end(as1);

    return ss;
}


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void
assert_perror(int cond, const char* text)
{
    if (cond) {
        return;
    }

    perror(text);
    exit(1);
}

char*
read_whole_file(const char* path)
{
    int rv = 0;
    struct stat info;
    
    rv = stat(path, &info);
    assert_perror(rv == 0, "stat");

    char* buff = malloc(info.st_size);
    FILE* ff = fopen(path, "r");
    assert_perror(ff != 0, "fopen");

    int nn = fread(buff, info.st_size, 1, ff);
    assert_perror(nn == info.st_size, "fread");

    rv = fclose(ff);
    assert_perror(rv == 0, "fclose");

    return buff;
}


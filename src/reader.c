
#include <string.h>

#include "mem.h"
#include "reader.h"
#include "io.h"

ps_source*
source_from_string(const char* text)
{
    ps_source* code = ALLOC(ps_source);
    code->path = strdup("[string]");
    code->text = strdup(text);
    return code;
}

ps_source*
source_from_path(const char* path)
{
    ps_source* code = ALLOC(ps_source);
    code->path = strdup(path);
    code->text = read_whole_file(path);
    return code;
}



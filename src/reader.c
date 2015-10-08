
#include "reader.h"

ps_source*
open_string(const char* text)
{
    ps_source* code = ALLOC(ps_source);
    code->path = strdup("[string]");
    code->text = strdup(text);
    return code;
}



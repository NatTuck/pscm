#ifndef PSCM_IO_H
#define PSCM_IO_H

void assert_perror(int, const char*);
void hard_assert(int, const char*);

char* read_whole_file(const char*);

char* pscm_sprintf(const char* fmt, ...);
#endif

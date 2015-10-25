#ifndef PSCM_ERRORS_H
#define PSCM_ERRORS_H

void fatal_error(const char*);
void assert_perror(int, const char*);
void hard_assert(int, const char*);

#endif

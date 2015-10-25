#ifndef PSCM_ERRORS_H
#define PSCM_ERRORS_H

#define fatal_error(m) fatal_error_real((m), __FILE__, __LINE__)
#define assert_perror(x, m) assert_perror_real((x), (m), __FILE__, __LINE__)
#define hard_assert(x, m) hard_assert_real((x), (m), __FILE__, __LINE__)

void fatal_error_real(const char*, const char*, int);
void assert_perror_real(int, const char*, const char*, int);
void hard_assert_real(int, const char*, const char*, int);

#endif

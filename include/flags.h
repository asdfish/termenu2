#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>

extern const char* flag_delimiter;
extern bool flag_password;

extern int flags_parse(int argc, const char* restrict argv[]);

#endif

#ifndef STRING_H
#define STRING_H

#include <stddef.h>

extern size_t string_count(const char* string, const char* restrict delimiter);
extern int string_separate(char* string, const char* restrict delimiter, const char*** restrict output, size_t* restrict output_length);

#endif

#ifndef STRING_H
#define STRING_H

#include <stddef.h>

extern size_t string_count(const char* string, const char* delimiter);
extern int string_separate(const char* string, const char* delimiter, const char*** output, size_t* output_length);

#endif

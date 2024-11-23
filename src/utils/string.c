#include <utils/string.h>

#include <string.h>

size_t string_count(const char* string, const char* delimiter) {
  if(!string || !delimiter)
    return 0;

  char* string_p = (char*) string;

  size_t string_length = strlen(string);
  size_t delimiter_length = strlen(delimiter);

  size_t count = 0;

  while((string_p = strstr(string_p, delimiter))) {
    count ++;

    if(string_p - string + string_length < string_length)
      string_p += delimiter_length;
    else
      string_p ++;
  }

  return count;
}

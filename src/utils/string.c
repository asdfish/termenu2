#include <utils/string.h>

#include <stdlib.h>
#include <string.h>

size_t string_count(const char* string, const char* restrict delimiter) {
  if(!string || !delimiter)
    return 0;

  char* string_p = (char*) string;

  size_t string_length = strlen(string);
  size_t delimiter_length = strlen(delimiter);

  size_t count = 0;

  while((string_p = strstr(string_p, delimiter))) {
    count ++;

    if((size_t) (string_p - string) < string_length)
      string_p += delimiter_length;
    else
      break;
  }

  return count;
}
int string_separate(char* string, const char* restrict delimiter, const char*** restrict output, size_t* restrict output_length) {
  if(!string || !delimiter || !output || !output_length)
    return -1;

  size_t separated_length = string_count(string, delimiter);
  if(separated_length == 0)
    return 0;
  const char** separated = (const char**) malloc(separated_length * sizeof(const char*));
  if(!separated)
    return -1;

  char* string_p = string;

  size_t i = 0;
  while(string_p) {
    if(i > separated_length)
      break;
    separated[i] = string_p;

    strsep(&string_p, delimiter);
    i ++;
  }

  *output = separated;
  *output_length = i;
  return 0;
}

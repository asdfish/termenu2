#include <path.h>

#include <stdlib.h>

int path_get_executables(const char*** executables, size_t* executables_length) {
  if(!executables || !executables_length)
    return -1;

  const char* path = getenv("PATH");
  if(!path)
    return -1;

  return 0;
}

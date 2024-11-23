#include <commands/exec.h>
#include <flags.h>
#include <utils/string.h>

#include <stdlib.h>
#include <stdio.h>

int command_exec(int argc, const char* restrict argv[]) {
  char* path = getenv("PATH");
  if(!path)
    return -1;

  const char** paths = NULL;
  size_t paths_length = 0;
  if(string_separate(path, flag_delimiter, &paths, &paths_length) != 0)
    return -1;
  
  free(paths);
  paths = NULL;
  return 0;
}

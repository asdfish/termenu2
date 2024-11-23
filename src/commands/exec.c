#include <commands/exec.h>
#include <flags.h>
#include <utils/dirent.h>
#include <utils/macros.h>
#include <utils/string.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int get_executables(const char*** output, size_t* output_length) {
  if(!output || !output_length)
    return -1;

  char* path = getenv("PATH");
  if(!path || !strlen(path)) {
    printf("PATH not found\n");
    return -1;
  }

  const char** path_separated = NULL;
  size_t path_separated_length = 0;
  if(string_separate(path, flag_delimiter, &path_separated, &path_separated_length) != 0) {
    printf("Failed to allocate memory\n");
    return -1;
  }

  size_t executables_length = 0;
  for(size_t i = 0; i < path_separated_length; i ++)
    executables_length += dirent_get_length(path_separated[i], DIRENT_IS_FILE);
  if(!executables_length) {
    printf("No executables were found\n");
    goto free_path_separated;
  }

  const char** executables = (const char**) malloc(executables_length * sizeof(const char*));
  if(!executables) {
    printf("Failed to allocate memory\n");
    goto free_path_separated;
  }

  size_t i = 0;
  for(size_t j = 0; j < path_separated_length; j ++) {
    DIR* directory_pointer = opendir(path_separated[j]);
    if(!directory_pointer)
      continue;

    struct dirent* dirent_pointer = NULL;
    while((dirent_pointer = readdir(directory_pointer)))
      if(dirent_meets_condition(dirent_pointer, DIRENT_IS_FILE)) {
        if(i >= executables_length)
          goto exit_success;

        size_t executable_path_length = strlen(path_separated[j]) + 1 + strlen(dirent_pointer->d_name);

        executables[i] = malloc((executable_path_length + 1) * sizeof(char));
        if(!executables[i]) {
          printf("Failed to allocate memory\n");

          closedir(directory_pointer);
          goto free_executables_contents;
        }

        if(!snprintf((char*) executables[i], executable_path_length + 1, "%s/%s", path_separated[j], dirent_pointer->d_name)) {
          printf("sprintf failure\n");

          closedir(directory_pointer);
          i ++;
          goto free_executables_contents;
        }

        i ++;
      }
    closedir(directory_pointer);
  }

exit_success:
  *output = executables;
  *output_length = i;
  FREE(path_separated);
  return 0;

free_executables_contents:
  for(size_t j = 0; j < i; j ++)
    FREE_STRING(executables[j]);
  FREE(executables);
free_path_separated:
  FREE(path_separated);
  return -1;
}

int command_exec(int argc, const char* restrict argv[]) {
  const char** executables = NULL;
  size_t executables_length = 0;
  if(get_executables(&executables, &executables_length) != 0)
    return -1;

  for(size_t i = 0; i < executables_length; i ++) {
    printf("%s\n", executables[i]);
    FREE_STRING(executables[i]);
  }
  FREE(executables);
  return 0;
}

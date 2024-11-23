#include <commands/exec.h>
#include <flags.h>
#include <utils/dirent.h>
#include <utils/macros.h>
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

  const char*** paths_files = (const char***) malloc(paths_length * sizeof(const char**));
  if(!paths_files)
    goto free_paths;
  size_t* paths_lengths = (size_t*) malloc(paths_length * sizeof(size_t));
  if(!paths_length)
    goto free_paths_files;

  size_t true_paths_length = 0;
  for(size_t i = 0; i < paths_length; i ++) {
    paths_files[i] = NULL;
    paths_lengths[i] = 0;

    if(dirent_get_paths(paths[i], DIRENT_IS_FILE, paths_files + true_paths_length, paths_lengths + true_paths_length) == 0)
      true_paths_length ++;
  }

  FREE(paths);

  for(size_t i = 0; i < true_paths_length; i ++) {
    for(size_t j = 0; j < paths_lengths[i]; j ++)
      FREE_STRING(paths_files[i][j]);
    FREE(paths_files[i]);
  }

  FREE(paths_lengths);
free_paths_files:
  FREE(paths_files);
free_paths:
  FREE(paths);
  return 0;
}

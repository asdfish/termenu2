#include <utils/dirent.h>
#include <utils/macros.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool dirent_meets_condition(struct dirent* dirent, enum DirentCondition condition) {
  if(!dirent)
    return false;

  switch(condition) {
    case DIRENT_IS_DIRECTORY:
      if(dirent->d_type == DT_DIR && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
        return true;
      break;
    case DIRENT_IS_FILE:
      if(dirent->d_type == DT_REG)
        return true;
      break;
  }

  return false;
}
size_t dirent_get_length(const char* path, enum DirentCondition condition) {
  DIR* directory_pointer = opendir(path);
  if(!directory_pointer)
    return 0;

  size_t length = 0;
  struct dirent* dirent_pointer = NULL;
  while((dirent_pointer = readdir(directory_pointer)))
    if(dirent_meets_condition(dirent_pointer, condition))
      length ++;
  closedir(directory_pointer);

  return length;
}
int dirent_get_paths(const char* path, enum DirentCondition condition, const char*** output, size_t* output_length) {
  if(!path || !output || !output_length)
    return -1;

  size_t directory_length = dirent_get_length(path, condition);
  if(!directory_length)
    return -1;

  DIR* directory_pointer = opendir(path);
  if(!directory_pointer)
    return -1;

  const char** dirent_paths = (const char**) malloc(directory_length * sizeof(const char*));
  if(!dirent_paths)
    goto closedir;

  if(chdir(path) != 0)
    goto free_dirent_paths;

  size_t i = 0;
  struct dirent* dirent_pointer = NULL;
  while((dirent_pointer = readdir(directory_pointer))) {
    if(i >= directory_length)
      break;

    dirent_paths[i] = realpath(dirent_pointer->d_name, NULL);
    if(!dirent_paths[i])
      goto free_dirent_paths_contents;

    i ++;
  }

  closedir(directory_pointer);

  *output = dirent_paths;
  *output_length = i;
  return 0;

free_dirent_paths_contents:
  for(size_t j = 0; j < i; j ++)
    FREE_STRING(dirent_paths[j]);
free_dirent_paths:
  FREE(dirent_paths);
closedir:
  closedir(directory_pointer);
  return -1;
}

#include <utils/dirent.h>
#include <utils/macros.h>

#include <stdlib.h>
#include <string.h>

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
int dirent_get_names(const char* path, enum DirentCondition condition, const char*** output, size_t* output_length) {
  if(!path || !output || !output_length)
    return -1;

  size_t directory_length = dirent_get_length(path, condition);
  if(!directory_length)
    return -1;

  DIR* directory_pointer = opendir(path);
  if(!directory_pointer)
    return -1;

  const char** dirent_names = (const char**) malloc(directory_length * sizeof(const char*));
  if(!dirent_names)
    goto closedir;

  size_t i = 0;
  struct dirent* dirent_pointer = NULL;
  while((dirent_pointer = readdir(directory_pointer))) {
    if(i >= directory_length)
      break;

    dirent_names[i] = strdup(dirent_pointer->d_name);
    if(!dirent_names[i])
      goto free_dirent_names_contents;

    i ++;
  }

  closedir(directory_pointer);

  *output = dirent_names;
  *output_length = i;
  return 0;

free_dirent_names_contents:
  for(size_t j = 0; j < i; j ++) {
    free((char*) dirent_names[j]);
    dirent_names[j] = NULL;
  }

  free(dirent_names);
  dirent_names = NULL;
closedir:
  closedir(directory_pointer);
  return -1;
}

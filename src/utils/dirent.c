#include <utils/dirent.h>
#include <utils/macros.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
bool dirent_meets_condition(struct dirent* dirent, enum DirentCondition condition) {
  if(!dirent)
    return false;

  switch(condition) {
    case DIRENT_IS_DIRECTORY:
      return dirent->d_type == DT_DIR && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0;
    case DIRENT_IS_FILE:
      return dirent->d_type == DT_REG;
  }

  return false;
}

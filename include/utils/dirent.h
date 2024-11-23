#ifndef DIRENT_H
#define DIRENT_H

#include <dirent.h>
#include <stdbool.h>

enum DirentCondition {
  DIRENT_IS_DIRECTORY,
  DIRENT_IS_FILE,
};

extern size_t dirent_get_length(const char* path, enum DirentCondition);
extern bool dirent_meets_condition(struct dirent* dirent, enum DirentCondition condition);

#endif

#ifndef DIRENT_H
#define DIRENT_H

#include <dirent.h>
#include <stdbool.h>

enum DirentCondition {
  DIRENT_IS_DIRECTORY,
  DIRENT_IS_FILE,
};

extern bool dirent_meets_condition(struct dirent* dirent, enum DirentCondition condition);
extern size_t dirent_get_length(const char* path, enum DirentCondition);
extern int dirent_get_paths(const char* path, enum DirentCondition condition, const char*** output, size_t* output_length);

#endif

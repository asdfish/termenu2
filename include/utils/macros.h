#ifndef MACROS_H
#define MACROS_H

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

#define MAX(x, y) (x > y ? x : y)

#define FREE(pointer) \
  if(pointer) {       \
    free(pointer);    \
    pointer = NULL;   \
  }
#define FREE_STRING(pointer) \
  if(pointer) {              \
    free((char*) pointer);   \
    pointer = NULL;          \
  }

#endif

#ifndef MACROS_H
#define MACROS_H

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

#define MAX(x, y) (x > y ? x : y)

#define EXIT(jump) { \
  exit_status = -1; \
  goto jump;\
}

#endif

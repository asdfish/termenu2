#include <utils/string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char* path = getenv("PATH");
  if(!path)
    return -1;

  const char** arr = NULL;
  size_t arr_len = 0;

  if(string_separate(path,":",&arr,&arr_len) != 0)
    return -1;

  if(arr) {
    for(size_t i = 0; i < arr_len; i ++) {
      printf("%s\n", arr[i]);
    }
    free(arr);
    arr = NULL;
  }

  return 0;
}

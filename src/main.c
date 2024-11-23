#include <utils/string.h>
#include <stdio.h>

int main(void) {
  size_t counts = string_count("aaaaaa", "aa");
  printf("%lu\n", counts);
  return 0;
}

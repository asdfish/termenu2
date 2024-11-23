#include <config.h>
#include <flags.h>

#include <unistd.h>
#include <stdio.h>

const char* flag_delimiter = ":";
bool flag_password = false;

int flags_parse(int argc, const char* restrict argv[]) {
  char c = -1;
  while((c = getopt(argc, (char* const*) argv, "d:p")) != -1) {
    switch(c) {
      case 'd':
        flag_delimiter = optarg;
        break;
      case 'p':
        flag_password = true;
        break;
    }
  }
  return 0;
}

#ifndef TYPES_H
#define TYPES_H

struct Command {
  const char* help;
  const char* name;
  int (*function) (int argc, const char* argv[]);
};

#endif

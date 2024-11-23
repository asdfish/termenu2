#define CONFIG_INCLUDE_COMMANDS
#include <commands/help.h>
#include <config.h>
#include <utils/macros.h>

#include <stddef.h>
#include <stdio.h>
#include <string.h>

int command_help(int argc, const char* restrict argv[]) {
  printf("Usage: %s [COMMAND] [OPTIONS]...\n"
      "Commands:\n", argv[0]);

  size_t max_command_length = 0;
  for(size_t i = 0; i < ARRAY_LENGTH(commands); i ++)
    max_command_length = MAX(max_command_length, strlen(commands[i].name));

  for(size_t i = 0; i < ARRAY_LENGTH(commands); i ++) {
    printf("\t%s", commands[i].name);

    size_t length = strlen(commands[i].name);
    while(length < max_command_length) {
      printf(" ");
      length ++;
    }

    printf(" - %s\n", commands[i].help);
  }

  printf("Options:\n"
         "\t-d - set delimiter\n"
         "\t-p - enable password hiding\n");

  return 0;
}

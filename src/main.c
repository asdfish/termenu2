#define CONFIG_INCLUDE_COMMANDS
#include <config.h>
#include <commands/help.h>
#include <flags.h>
#include <utils/macros.h>

#include <stdio.h>
#include <string.h>

int main(int argc, const char* restrict argv[]) {
  if(argc == 1) {
    printf("No command specified\n");
    return command_help(argc, argv);
  }

  ssize_t command_index = -1;
  for(size_t i = 0; i < ARRAY_LENGTH(commands); i ++)
    if(strcmp(argv[1], commands[i].name) == 0)
      command_index = i;

  if(command_index == -1) {
    printf("Command not found: %s\n", argv[1]);
    return command_help(argc, argv);
  }

  if(flags_parse(argc, argv) != 0)
    return -1;

  return commands[command_index].function(argc, argv);
}

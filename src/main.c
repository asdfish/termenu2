#define CONFIG_INCLUDE_COMMANDS
#include <config.h>
#include <commands/help.h>
#include <utils/macros.h>

#include <string.h>

int main(int argc, const char* argv[]) {
  if(argc == 1)
    return command_help(argc, argv);

  for(size_t i = 0; i < ARRAY_LENGTH(commands); i ++)
    if(strcmp(commands[i].name, argv[1]) == 0)
      return commands[i].function(argc, argv);

  return command_help(argc, argv);
}

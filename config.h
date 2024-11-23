#ifndef CONFIG_H
#define CONFIG_H

#ifdef CONFIG_INCLUDE_COMMANDS
#include <commands/exec.h>
#include <commands/help.h>
#include <types.h>
static const struct Command commands[] = {
  { "dmenu_run equivalent", "exec", command_exec },
  { "print this message",   "help", command_help },
};
#endif

#endif

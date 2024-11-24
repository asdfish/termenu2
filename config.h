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

#ifdef CONFIG_INCLUDE_MENU
#include <termbox2.h>

static const uintattr_t menu_background = TB_BLACK;
static const uintattr_t menu_background_reversed = TB_WHITE;
static const uintattr_t menu_item_foreground = 0;
static const uintattr_t menu_item_foreground_reversed = TB_BLACK;
#endif

#endif

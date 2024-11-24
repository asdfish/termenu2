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

static const uintattr_t filter_foreground = TB_WHITE;
static const uintattr_t filter_background = TB_BLACK;

static const uintattr_t menu_background = TB_BLACK;
static const uintattr_t menu_background_reversed = TB_WHITE;
static const uintattr_t menu_item_foreground = 0;
static const uintattr_t menu_item_foreground_reversed = TB_BLACK;
#endif

#define KEY_QUIT TB_KEY_ESC

#define KEY_UP   TB_KEY_ARROW_UP
#define KEY_DOWN TB_KEY_ARROW_DOWN

// if TB_KEY_BACKSPACE does not work try TB_KEY_BACKSPACE2
#define KEY_DELETE TB_KEY_BACKSPACE2

#define KEY_SUBMIT TB_KEY_ENTER

#endif

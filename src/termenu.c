#define CONFIG_INCLUDE_MENU
#include <config.h>
#include <termenu.h>
#include <utils/macros.h>

#include <orchestra/orchestra.h>

static o_string filter;
static struct TbMenu menu;

static bool redraw_filter = true;
static bool redraw_menu = true;

static bool submit = false;

static int handle_event(struct tb_event* event);
static int handle_key(struct tb_event* event);
static int handle_resize(void);

static int handle_event(struct tb_event* event) {
  switch(event->type) {
    case TB_EVENT_KEY:
      return handle_key(event);
    case TB_EVENT_RESIZE:
      return handle_resize();
    default:
      return 0;
  }
}
static int handle_key(struct tb_event* event) {
  switch(event->key) {
    case KEY_QUIT:
      return -1;
      break;
    case KEY_UP:
      redraw_menu = true;
      if(tb_menu_move_cursor(&menu, -1) != TBM_SUCCESS)
        return -1;
      break;
    case KEY_DOWN:
      redraw_menu = true;
      if(tb_menu_move_cursor(&menu, 1) != TBM_SUCCESS)
        return -1;
      break;
    case KEY_DELETE:
      if(strlen(filter.contents) != 0) {
        if(o_string_delete(&filter, strlen(filter.contents) - 1, 1) != O_SUCCESS)
          return -1;
        if(tb_menu_filter(&menu, filter.contents) != TBM_SUCCESS)
          return -1;
        redraw_filter = true;
        redraw_menu = true;
      }
      break;
    case KEY_SUBMIT:
      submit = true;
      break;
  }

  if(event->ch != 0) {
    char tail[2] = " \0";
    tail[0] = event->ch;
    if(o_string_cat(&filter, tail) != O_SUCCESS)
      return -1;
    if(tb_menu_filter(&menu, filter.contents) != TBM_SUCCESS)
      return -1;
    redraw_filter = true;
    redraw_menu = true;
  }
  return 0;
}
static int handle_resize(void) {
  menu.width = tb_width();
  menu.height = tb_height() - 1;
  return 0;
}

int termenu_run(struct TbMenuItem* menu_items, size_t items_length, size_t* output) {
  menu.x = 0;
  menu.y = 1;
  menu.background = menu_background;
  menu.background_reversed = menu_background_reversed;
  menu.enable_reversed_colors = true;

  if(tb_menu_init(&menu) != TBM_SUCCESS)
    return -1;
  if(tb_menu_set_items(&menu, menu_items, items_length) != TBM_SUCCESS)
    goto tb_menu_uninit;

  if(o_string_init(&filter) != O_SUCCESS)
    goto tb_menu_uninit;

  size_t max_name_length = 0;
  for(size_t i = 0; i < items_length; i ++)
    max_name_length = MAX(max_name_length, strlen(menu_items[i].contents));
  if(o_string_reserve(&filter, max_name_length) != O_SUCCESS)
    goto o_string_uninit;

  tb_init();
  handle_resize();
  while(!submit) {
    if(redraw_filter || redraw_menu) {
      tb_clear();
      if(redraw_filter) {
        tb_print(0, 0, 0, 0, filter.contents);
        redraw_filter = false;
      }
      if(redraw_menu) {
        tb_menu_draw(&menu);
        redraw_menu = false;
      }
      tb_present();
    }

    struct tb_event event;
    tb_poll_event(&event);

    if(handle_event(&event) != 0)
      goto tb_shutdown;
  }

  tb_shutdown();
  o_string_uninit(&filter);
  tb_menu_uninit(&menu);
  return 0;

tb_shutdown:
  tb_shutdown();
o_string_uninit:
  o_string_uninit(&filter);
tb_menu_uninit:
  tb_menu_uninit(&menu);
  return -1;
}

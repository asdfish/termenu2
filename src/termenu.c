#define CONFIG_INCLUDE_MENU
#include <config.h>
#include <termenu.h>

struct TbMenu menu;

static void handle_resize(void) {
  menu.width = tb_width();
  menu.height = tb_height() - 1;
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

  tb_init();
  handle_resize();
  while(1) {
    tb_menu_draw(&menu);
    tb_present();

    struct tb_event event;
    tb_poll_event(&event);

    if(event.type == TB_EVENT_RESIZE)
      handle_resize();

    if(event.ch == 'q')
      break;
  }

  tb_shutdown();
  tb_menu_uninit(&menu);
  return 0;

tb_shutdown:
  tb_shutdown();
tb_menu_uninit:
  tb_menu_uninit(&menu);
  return -1;
}

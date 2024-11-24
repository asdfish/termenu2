#include <termenu.h>

struct TbMenu menu;

static int handle_resize(void) {
  menu.width = tb_width();
}

int termenu_init(struct TbMenuItem* menu_items) {
  tb_menu_init(&menu);
}

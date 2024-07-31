#include "../inc/mc.h"

int main() {
  void *handle;
  void (*apply_color_scheme)();

  Panel *panel_one = malloc(sizeof(Panel));
  Panel *panel_second = malloc(sizeof(Panel));
  if (panel_one == NULL || panel_second == NULL) {
    perror("Не удалось выделить память для панелей");
    endwin();
    return 1;
  }
  init_ncurses_plugins(&handle, &apply_color_scheme);
  init_panel(panel_one, ".");
  init_panel(panel_second, ".");
  int selected_panel = 0;
  int ch = 'W';
  while (ch != 'q') {
    printTwoDir(panel_one, panel_second);
    ch = getch();
    switch (ch) {
      case KEY_UP:
        selected_panel == 0 ? navigate_panel(panel_one, -1)
                            : navigate_panel(panel_second, -1);
        break;
      case KEY_DOWN:
        selected_panel == 0 ? navigate_panel(panel_one, 1)
                            : navigate_panel(panel_second, 1);
        break;
      case '\n':
        selected_panel == 0 ? read_or_change(panel_one)
                            : read_or_change(panel_second);
        break;
      case '\t':
        switch_panel(&selected_panel);
        break;
    }
    refresh();
  }

  free_panel(panel_one);
  free_panel(panel_second);
  off_color_sheme(handle);
  return 0;
}
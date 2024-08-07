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
  char *root_home = get_root_path();  // Получаем путь до корня
  if (NULL == root_home) {
    off_color_sheme(handle);
    free(panel_one);
    free(panel_second);
    endwin();
  }
  // путь к корневой директории
  int len = strlen(root_home);
  char root_path[len + 1];  // +1 для завершающего нуля
  snprintf(root_path, sizeof(root_path), "%s/", root_home);

  init_panel(panel_one, root_path);
  init_panel(panel_second, root_path);
  free(root_home);
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
  free(panel_one);
  free(panel_second);
  off_color_sheme(handle);
  return 0;
}
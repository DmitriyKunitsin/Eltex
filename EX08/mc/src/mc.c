#include "../inc/mc.h"

int main() {

  //   initscr(); /// Инициализация ncrses
  //   noecho();  /// Отключить ввод в командную строку
  //   keypad(stdscr, TRUE); /// Включить специальные клавиши
  //   curs_set(0);          /// спрятать курсор
  void *handle;
  void (*apply_color_scheme)();

  init_ncurses_plugins(&handle, &apply_color_scheme);
  // Инициализация панелей
  Panel *panel_one = malloc(sizeof(Panel)); // Выделяем память для panel_one
  Panel *panel_second =
      malloc(sizeof(Panel)); // Выделяем память для panel_second
  if (panel_one == NULL || panel_second == NULL) {
    perror("Failed to allocate memory for panels");
    endwin();
    return 1; // Завершаем программу при ошибке выделения памяти
  }
  init_panel(panel_one, ".");
  init_panel(panel_second, ".");

  int ch = 'W';
  while (ch != 'q') {
    ch = getch();
    switch (ch) {
    case KEY_UP:
      /// TODO : выделить вверх
      clear();
      mvprintw(10, 10, "HELLO WORLD KEY_UP");

      break;
    case KEY_DOWN:
      /// TODO : выделить вниз
      // mvprintw(10, 10, "BAY WORLD KEY_DOWN");
      printTwoDir(panel_one, panel_second);

      break;
    case '\n':
      /// TODO : выбор, действие
      break;
    case '\t':
      /// TODO : TAB
      break;
    }
    refresh();
  }

  free_panel(panel_one);
  free_panel(panel_second);
  off_color_sheme(handle);
  endwin();
  return 0;
}
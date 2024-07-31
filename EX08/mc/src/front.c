#include "../inc/front.h"

void printTwoDir(Panel *panel, Panel *panelDouble) {
  clear();
  // Получаем размеры терминала
  int height, width;
  getmaxyx(stdscr, height, width);

  // ширина каждой панели
  int panelWidth = width / 2;
  PRINT_INFO_CONTROLLER;
  // рамки для панелей
  for (int i = 2; i < height; ++i) {
    mvaddch(i, 0, '|');  // Левая граница первой панели
    mvaddch(i, panelWidth - 1, '|');  // Правая граница первой панели
    mvaddch(i, panelWidth, '|');  // Левая граница второй панели
    mvaddch(i, width - 1, '|');  // Правая граница второй панели
  }

  // горизонтальные границы
  mvhline(2, 0, '-', width);           // Верхняя граница
  mvhline(height - 1, 0, '-', width);  // Нижняя граница

  // первая панель с данными
  for (int i = 0; i < panel->count; ++i) {
    if (panel->selected == i) {
      attron(A_REVERSE);
    }
    mvprintw(i + 3, 1, "%s", panel->files[i]);
    if (i == panel->selected) {
      attroff(A_REVERSE);
    }
  }

  // вторая панель данными
  for (int i = 0; i < panelDouble->count; ++i) {
    if (panelDouble->selected == i) {
      attron(A_REVERSE);
    }
    mvprintw(i + 3, panelWidth + 1, "%s", panelDouble->files[i]);
    if (i == panelDouble->selected) {
      attroff(A_REVERSE);
    }
  }
  refresh();
}

void print_file(FILE *file) {
  clear();
  char ch;
  int i = 0;
  int j = 0;
  while ((ch = fgetc(file)) != EOF) {
    if ('\n' == ch) {
      i++;
      j = 0;
    } else {
      mvprintw(i, j++, "%c", ch);
    }
  }
  mvprintw(i++, 0, "%s", "Q - for exit");
  refresh();
}
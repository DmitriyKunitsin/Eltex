#include "../inc/front.h"

void printTwoDir(Panel *panel, Panel *panelDouble) {
  clear();
  // Получаем размеры терминала
  int height, width;
  getmaxyx(stdscr, height, width);

  // Определяем ширину каждой панели
  int panelWidth = width / 2;
  PRINT_INFO_CONTROLLER;
  // Рисуем рамки для панелей
  for (int i = 2; i < height; ++i) {
    mvaddch(i, 0, '|'); // Левая граница первой панели
    mvaddch(i, panelWidth - 1, '|'); // Правая граница первой панели
    mvaddch(i, panelWidth, '|'); // Левая граница второй панели
    mvaddch(i, width - 1, '|'); // Правая граница второй панели
  }

  // Рисуем горизонтальные границы
  mvhline(2, 0, '-', width);          // Верхняя граница
  mvhline(height - 1, 0, '-', width); // Нижняя граница

  // Заполняем первую панель данными
  for (int i = 0; i < panel->count; ++i) {
    if (panel->selected == i) {
      attron(A_REVERSE);
    }
    mvprintw(i + 3, 1, "%s", panel->files[i]); // Сдвигаем на один символ вправо
    if (i == panel->selected) {
      attroff(A_REVERSE);
    }
  }

  // Заполняем вторую панель данными
  for (int i = 0; i < panelDouble->count; ++i) {
    mvprintw(i + 3, panelWidth + 1, "%s",
             panelDouble->files[i]); // Сдвигаем на один символ вправо
  }

  // Обновляем экран
  refresh();
}
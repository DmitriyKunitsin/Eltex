#include "../inc/plugin.h"

#include <dlfcn.h>
#include <ncurses.h>

void init_ncurses_plugins(
    void **handle, void (**apply_color_scheme)()) {  // Инициализация ncurses
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);  /// спрятать курсор

  // Загрузка плагина
  *handle = dlopen("mc/plugins/color_plugin.so", RTLD_LAZY);
  if (!*handle) {
    fprintf(stderr, "%s\n", dlerror());
    endwin();
    exit(1);
  }

  // Получение адреса функции плагина
  *apply_color_scheme = (void (*)())dlsym(*handle, "on_color_scheme");
  const char *error = dlerror();  // Проверка на ошибки после dlsym
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    dlclose(*handle);  // Освобождение библиотеки перед выходом
    endwin();  // Освобождение ресурсов ncurses
    exit(1);
  }

  // Применение цветовой схемы
  if (*apply_color_scheme) {
    (*apply_color_scheme)();
  }
}

void off_color_sheme(void *handle) {
  attroff(COLOR_PAIR(1));
  getch();
  endwin();

  // Освобождение библиотеки
  dlclose(handle);
}

#ifndef PLUGIN_H_
#define PLUGIN_H_
/**
 * @file plugin.h
 * @brief Модуль для подключения плагинов к файловому менеджеру
 */
#include "mc.h"
#include <dlfcn.h>

typedef enum {
  BLACK = COLOR_BLACK,
  WHITE = COLOR_WHITE,
  CYAN = COLOR_CYAN,
  BLUE = COLOR_BLUE,
  GREEN = COLOR_GREEN,
  RED = COLOR_RED,
  YELLOW = COLOR_YELLOW
} COLOR_LIST;

#define PLAGIN_PATH "mc/plugins/"
#define FILE_NAME "colors.txt"
#define DEFAULT_ONE_COLOR COLOR_CYAN
#define DEFAULT_SECOND_COLOR COLOR_BLACK

/**
 * @brief загрузка плагинов для цветовой палитры файлового менеджера
 * @param apply_color_scheme указатель на функцию
 * @param handle указатель для плагина
 */
void init_ncurses_plugins(void **handle, void (**apply_color_scheme)());

COLOR_LIST *read_color_with_file();
/**
 * @brief отключение цветовой палитры и плагина 
 * Так же функция выключает ncurses
 */
void off_color_sheme(void *handle);


#endif
#ifndef PLUGIN_H_
#define PLUGIN_H_

#include "mc.h"
#include <dlfcn.h>

/**
 * @brief загрузка плагинов для цветовой палитры файлового менеджера
 * @param apply_color_scheme указатель на функцию
 * @param handle указатель для плагина
 */
void init_ncurses_plugins(void **handle, void (**apply_color_scheme)());
/**
 * @brief отключение цветовой палитры и плагина 
 * Так же функция выключает ncurses
 */
void off_color_sheme(void *handle);

#endif
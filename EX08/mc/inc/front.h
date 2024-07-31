#ifndef FRONT_H_
#define FRONT_H_
/**
 * @file front.h
 * @brief Модуль реализации вывода на экран информации
 * тут все функции для вывода на экран информации о директориях
 */

#include "../inc/panel.h"
#include "mc.h"
/**
 * @brief Макрос выводи информационное меню по управлению
 */
#define PRINT_INFO_CONTROLLER do {mvprintw(1, 0, "%s", "UP_ARRAY - switch up , DOWN_ARRAY - switch down, TAB - return, Enter - open selected folder");} while(0)

/**
 * @brief Отрисовка двух панелей с дирректориями на экран
 */
void printTwoDir(Panel *panel, Panel *panelDouble);

#endif
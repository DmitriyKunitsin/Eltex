#ifndef FRONT_H_
#define FRONT_H_


#include "../inc/panel.h"
#include "mc.h"

#define SCREEN_SIZE_ALL_WIGHT 90
#define SCREEN_SIZE_ALL_HEIGHT 50

/**
 * @brief Отрисовка двух панелей с дирректориями на экран
 */
void printTwoDir(Panel *panel, Panel *panelDouble);

#endif
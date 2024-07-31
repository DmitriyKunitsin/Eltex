#ifndef BACK_H_
#define BACK_H_
/**
 * @file back.h
 * @brief Модуль реализации всей внутренеей логики программы
 */
#include "mc.h"
#include "../inc/panel.h"

#define MAX_FILES 100
#define MAX_PATH 1024

/**
 * @brief Изменения размера матрицы с файлами, если окажется недостаточно
 * @param panel Структура с информацией о дирректории
 * @param count_files колличество файлов в структуре на данный момент
 * Умножает на 2 текущий размер матрицы и меняет размер
 */
int resize_panel(Panel *panel, int count_files);
/**
 * @brief Инициализация панели и наполнение ее данными о переданной директории
 * @param panel Структура с информацией о дирректории
 * @param path Путь по которому необходимо спарсить данные
 */
void init_panel(Panel *panel, const char *path);
/**
 * @brief Очищение памяти, выделенной для панели
 */
void free_panel(Panel *panel);

#endif
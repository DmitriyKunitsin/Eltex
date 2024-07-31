#ifndef PANEL_H_
#define PANEL_H_
/**
 * @file panel.h
 * @brief Модуль структуры данных
 */

/**
 * @brief Структура для реализации панели управления файловым менеджером
 * @param files название файла, под нужным индексом
 * @param count кол-во файлов в данной директории
 * @param selected выбранный файл, для выделения
 * @param path путь где мы сейчас находимся
 */
typedef struct {
    char **files;
    char *path;
    int count;
    int selected;
} Panel;

#endif 
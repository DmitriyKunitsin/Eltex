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
/**
 * @brief Смещает выбранную панель
 */
void navigate_panel(Panel *panel, int dirrection);
/**
 * @brief Смена выбранной панели
 */
void switch_panel(int *selected_panel);
/**
 * @brief Меняет директорию в зависимости от выбора пользователя
 */
void change_directory(Panel *panel);
/**
 * @brief Чтение файла и вывод его на экран
 */
void read_file(const char *selectected_file);
/**
 * @brief Читать или менять директорию
 * Функция понимает, что перед ней, дирректория или файл для чтения
 */
void read_or_change(Panel *panel);
/**
 * @brief возвращает в предыдущую директорию
 */
void back_directiry(Panel *panel);
/**
 * @brief возвращает путь от корневой папки до текущей
 */
char* get_root_path();
#endif
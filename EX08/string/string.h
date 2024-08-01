#ifndef STRING_H_
#define STRING_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Макрос названия файла
 * Используется для избежания опечаток
 */
#define FILE_NAME "output.txt"
/**
 * @brief Запись в нужный файл строки
 * Если файла нет такого, то создаст
 */
void write_file();
/**
 * @brief Перевыделение память под строку для считывания из файла
 */
int realloc_string(char *string, int *size);
/**
 * @brief Чтение из нужного файла
 */
char *read_file();

#endif
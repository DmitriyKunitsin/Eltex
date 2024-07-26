#ifndef CALC_H
#define CALC_H

#include <stdio.h>

/**
 * @file calc.h
 * @brief реализация калькулятора
 * @author Дмитрий Куницин
 */
/**
 * @brief сложение
 * @returns складывает первый аргумент с вторым
 */
float add(float a, float b);
/**
 * @brief вычитание
 * @returns отнимает первый аргумент от второго
 */
float sub(float a, float b);
/**
 * @brief умножение
 * @returns умножает первый аргумент на второй
 */
float mul(float a, float b);
/**
 * @brief деление
 * @returns делит первый аргумент на второй
 */
float div(float a, float b);
/**
 * @brief вывод меню на консоль
 */
void print_menu();
/**
 * @brief ввод пользователя 
 * Делает проверку, что пользователь ввел число
 * @returns возвращает корректный ввод пользователя
 */
float input(int a);
/**
 * @brief Вывод результата
 * Если результат без остатка, 
 * то выводит как целое, иначе выводит с остатком
 */
void printResult(float res);

#endif
/*Найти количество единиц в двоичном представлении целого
положительного числа (число вводится с клавиатуры)*/

#include "function.h"


int main() {
 printf("Задание №3\n");
  int val = 0;
  __uint8_t checkValidation = 0;
  do {
    printf("Введите положительное число: ");
    if ((checkValidation = scanf("%d", &val)) != 1 || val < 0) {
      printf("Некорректный ввод. Пожалуйста, введите положительное число.\n");
      while (getchar() != '\n')
        ;  // Очистка буфера ввода
    }
  } while (checkValidation != 1 || val < 0);

    printf("Колличество единиц :%d\n", counter_bit(val));

    return 0;
}
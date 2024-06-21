/*Вывести двоичное представление целого отрицательного числа,
используя битовые операции (число вводится с клавиатуры).*/

#include "function.h"

int main() {
  printf("Задание №2\n");
  int val = 0;
  __uint8_t checkValidation = 0;
  do {
    printf("Введите отрицательное число: ");
    if (((checkValidation = scanf("%d", &val)) != 1) || val >= 0) {
      printf("Некорректный ввод. Пожалуйста, введите отрицательное число.\n");
      while (getchar() != '\n') {
      };
    }
  } while (checkValidation != 1 || val >= 0);

  print_all_bit(val);

  return 0;
}
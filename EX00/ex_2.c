/*Вывести двоичное представление целого отрицательного числа,
используя битовые операции (число вводится с клавиатуры).*/

#include "function.h"

int main() {
  printf("Задание №2\n");
  int val = 0;
  __uint8_t checkValidation = 0;
  do {
    printf("Введите положительное число: ");
    if ((checkValidation = scanf("%d", &val)) != 1) {
      printf("Некорректный ввод. Пожалуйста, введите число.\n");
      while (getchar() != '\n') {
      };
    }
  } while (checkValidation != 1);

  print_all_bit(val);

  return 0;
}
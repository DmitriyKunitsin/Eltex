
#include "function.h"

/*Вывести двоичное представление целого положительного числа,
используя битовые операции (число вводится с клавиатуры). */

int main() {
  printf("Задание №1\n");
  int val = 0;
  __uint8_t checkValidation = 0;
  do {
    printf("Введите положительное число: ");
    if ((checkValidation = scanf("%d", &val)) != 1 || val < 0) {
      printf("Некорректный ввод. Пожалуйста, введите положительное число.\n");
      while (getchar() != '\n') {
      };  // Очистка буфера ввода
    }
  } while (checkValidation != 1 || val < 0);

  print_u_bit(val);

  return 0;
}
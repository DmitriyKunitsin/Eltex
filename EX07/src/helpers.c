#include "../include/calc.h"

void print_menu() {
  printf("Выберите операцию:\n");
  printf("1) Сложение\n");
  printf("2) Вычитание\n");
  printf("3) Умножение\n");
  printf("4) Деление\n");
  printf("5) Выход\n");
}

float input(int a) {
  float val = 0;
  int checkValidation = 0;
  do {
    printf("Введите %d число: ", a);
    if ((checkValidation = scanf("%f", &val)) != 1) {
      printf("Некорректный ввод. Пожалуйста, введите число.\n"); while (getchar() != '\n') {
      };
    }
  } while (checkValidation != 1);
  return val;
}

void printResult(float res) {
  if ((int)res == res) {
    printf("Результат: %0.f\n", res);
  } else {
    printf("Результат: %.1f\n", res);
  }
}
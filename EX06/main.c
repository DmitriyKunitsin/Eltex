#include "inc/calc.h"
#include <stdio.h>
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
int main() {
  int choice;
  float a, b;

  while (1) {
    print_menu();
    printf("Введите номер пункта: ");
    scanf("%d", &choice);

    if (choice == 5) {
      break; // Выход из программы
    }

    printf("Введите два числа: ");
    a = input(1);
    b = input(2);
    // scanf("%f %f", &a, &b);

    switch (choice) {
    case 1:
      printResult(add(a, b));
      break;
    case 2:
      printResult(sub(a, b));
      break;
    case 3:
      printResult(mul(a, b));
      break;
    case 4:
      if (b == 0) {
        printf("Ошибка: Деление на ноль!\n");
      } else {
        printResult(div(a, b));
      }
      break;
    default:
      printf("Неверный выбор! Пожалуйста, попробуйте снова.\n");
    }
  }

  return 0;
}
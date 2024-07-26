#include "inc/calc.h"

int main() {
  int choice;
  float a, b;

  while (1) {
    print_menu();
    printf("Введите номер пункта: ");
    scanf("%d", &choice);

    if (choice == 5) {
      break;
    }

    printf("Введите два числа: ");
    a = input(1);
    b = input(2);

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
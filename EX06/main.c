#include <stdio.h>
#include "inc/calc.h"
void print_menu() {
    printf("Выберите операцию:\n");
    printf("1) Сложение\n");
    printf("2) Вычитание\n");
    printf("3) Умножение\n");
    printf("4) Деление\n");
    printf("5) Выход\n");
}



int main() {
    int choice, a, b;

    while (1) {
        print_menu();
        printf("Введите номер пункта: ");
        scanf("%d", &choice);

        if (choice == 5) {
            break; // Выход из программы
        }

        printf("Введите два целых числа: ");
        scanf("%d %d", &a, &b);

        switch (choice) {
            case 1:
                printf("Результат: %d\n", add(a, b));
                break;
            case 2:
                printf("Результат: %d\n", sub(a, b));
                break;
            case 3:
                printf("Результат: %d\n", mul(a, b));
                break;
            case 4:
                if (b == 0) {
                    printf("Ошибка: Деление на ноль!\n");
                } else {
                    printf("Результат: %d\n", div(a, b));
                }
                break;
            default:
                printf("Неверный выбор! Пожалуйста, попробуйте снова.\n");
        }
    }

    return 0;
}
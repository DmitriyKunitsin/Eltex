#include "function.h"

void printArray(int *arr) {
    for(int i = 1; i <= 10; ++i) {
        *arr = i;
        printf("%d\n", *arr++);
    }
}

int changeThirdByte(int value) {
  int inputUserValue = input();
  char* ptr;
  ptr = (char*)&value;
  ptr += 3;
  *ptr = inputUserValue;
  printf("\n%d\n", value);
  return value;
}

int input() {
  int val = 0;
  __uint8_t checkValidation = 0;
  do {
    printf("Введите целое положительное число: ");
    if ((checkValidation = scanf("%d", &val)) != 1 || val < 0) {
      printf("Некорректный ввод. Пожалуйста, введите положительное число.\n");
      while (getchar() != '\n') {
      };  // Очистка буфера ввода
    }
  } while (checkValidation != 1 || val < 0);
  return val;
}
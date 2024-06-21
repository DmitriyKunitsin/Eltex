#include "function.h"

void print_u_bit(const int num) {
  int size = (int)(sizeof(int) * 8 - 1);
  for (int i = size; i >= 0; --i) {
    printf("%d", (num >> i) & 1);
    if (i % 8 == 0 && i != 0) {
      printf(",");
    }
  }
  printf("\n");
}

int counter_bit(const int num) {
  int size = (int)(sizeof(int) * 8 - 1);
  int count = 0;
  for (int i = size; i >= 0; --i) {
    printf("%d", (num >> i) & 1);
    count = (((num >> i) & 1) == 1) ? count + 1 : count;
    if (i % 8 == 0 && i != 0) {
      printf(",");
    }
  }
  printf("\n");
  return count;
}

void swap_three_byte(int currentNumb, int mask) {
  currentNumb = currentNumb & 0x00FFFFFF;
  currentNumb = currentNumb | (mask << 24);
  print_u_bit(currentNumb);
  printf("\n%d\n", currentNumb);
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
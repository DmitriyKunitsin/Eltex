#include "function.h"

void printArray(int* arr) {
  for (int i = 1; i <= 10; ++i) {
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

int my_strlen(char* arr) {
  int i = 0;
  while (*arr != '\0') {
    arr++;
    i++;
  }
  return i;
}

int check(char* arr, char* sub, int len) {
  int valid = 1;
  for (int i = 0; i < len; ++i) {
    if (*arr != *sub) {
      valid = 0;
    }
  }
  return valid;
}
char* SearchStrk(char* arr, char* sub) {
  int count = 0;
  int res_len = my_strlen(sub);
  char* ptr;
  while (*arr != '\0') {
    if (*arr == *sub) {
      int valid = check(arr, sub, res_len);
      if (valid == 1) {
        ptr = arr;
        break;
      }
    }
    arr++;
    count++;
  }
  printf("Символ %d в строке, начинает подстроку\n", ++count);
  return ptr;
}
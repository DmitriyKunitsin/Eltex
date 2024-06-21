/*Найти количество единиц в двоичном представлении целого
положительного числа (число вводится с клавиатуры)*/

#include "function.h"

int main() {
  printf("Задание №3\n");
  int val = input();

  printf("Колличество единиц :%d\n", counter_bit(val));

  return 0;
}
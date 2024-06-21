/*Поменять в целом положительном числе (типа int) значение третьего
байта на введенное пользователем число (изначальное число также
вводится с клавиатуры)*/

#include "function.h"

int main() {
  printf("Задание №4\n");
  int val = input();
  int userInput = input();

  swap_three_byte(val, userInput);

  return 0;
}
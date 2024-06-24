/*
Вывести заданный массив размером N
в обратном порядке.
Пример:
Ввод –> 1 2 3 4 5
Вывод –> 5 4 3 2 1
*/
#include "function.h"

int main(void) {
  int arr[N];
  initArray(arr);
  printf("Ввод -> ");
  printfArray(arr);
  swapArray(arr);
  printf("Вывод -> ");
  printfArray(arr);
  
  return 0;
}
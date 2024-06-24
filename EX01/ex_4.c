/*
Заполнить матрицу числами от 1 до N2 ули
Пример:
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
*/
#include "function.h"

int main(void) {
  int matrix[N][N];
  int size = N;
  int y = 0;
  int x = 0;
  int conter = 1;
  int max = size - 1;
  while (conter <= size * size) {
    for (int i = x % size; i <= max; ++i) {
      matrix[y][i] = conter++;
    }
    for (int i = y % size + 1; i <= max; ++i) {
      matrix[i][max] = conter++;
    }
    y += 1;
    for (int i = max - 1; i >= x; --i) {
      matrix[max][i] = conter++;
    }
    max -= 1;
    for (int i = max; i >= y; --i) {
      matrix[i][x] = conter++;
    }
    x += 1;
  }
  printMatrix(matrix);
  return 0;
}
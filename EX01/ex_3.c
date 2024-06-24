/*
Заполнить верхний треугольник матрицы
а нижний 0.
Пример:
0 0 1
0 1 1
1 1 1
*/

#include "function.h"

int main(void) {
  int matrix[N][N];
  fillUpperTriangleWithOnes(matrix);
  printMatrix(matrix);

  return 0;
}
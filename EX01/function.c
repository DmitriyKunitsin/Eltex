#include "function.h"

void initMatrix(int (*matrix)[N]) {
  int counter = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      matrix[i][j] = ++counter;
    }
  }
}

void printMatrix(int matrix[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}
void initArray(int *arr) {
  for (int i = 0; i < N; ++i) {
    arr[i] = i;
  }
}

void printfArray(int arr[N]) {
  for (int i = 0; i < N; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void swapArray(int *arr) {
  int size = N;
  for (int i = 0; i < (size / 2); ++i) {
    int temp = arr[i];
    arr[i] = arr[size - i - 1];
    arr[size - i - 1] = temp;
  }
}

void fillUpperTriangleWithOnes(int (*matrix)[N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if ((i + (j + 1)) >= N) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }
    }
  }
}

void fillMatrixInSpiralOrder(int (*matrix)[N]) {
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
}
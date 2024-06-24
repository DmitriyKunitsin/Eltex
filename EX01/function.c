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
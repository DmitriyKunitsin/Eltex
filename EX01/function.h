#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>

#define N 5

void initMatrix(int (*matrix)[N]);
void printMatrix(int matrix[N][N]);
void initArray(int *arr);
void printfArray(int arr[N]);
void swapArray(int *arr);
void fillUpperTriangleWithOnes(int (*matrix)[N]);

#endif
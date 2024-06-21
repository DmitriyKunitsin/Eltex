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

void print_all_bit(const int num) {
  int size = (int)(sizeof(int) * 8);
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
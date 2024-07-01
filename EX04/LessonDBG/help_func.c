#include "Pass.h"

int IsPassOk(void) {
  char Pass[12];
  gets(Pass);
  return 0 == strcmp(Pass, "test");
}
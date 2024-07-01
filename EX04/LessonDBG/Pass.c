
#include "Pass.h"

int main(void) {
  int PwStatus;
  puts("Enter password:");
  PwStatus = IsPassOk();
  if (PwStatus == 0) {
    printf("Bad password!\n");
    exit(1);
  } else {
    printf("Access granted!\n");
  }
  return 0;
}

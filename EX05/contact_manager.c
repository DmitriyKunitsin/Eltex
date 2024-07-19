#include "contact_manager.h"
int main(void) {
  int input = 0;
  struct list *Contacts = db_created();
  do {
    printMenu();
    scanf("%d", &input);
    while (getchar() != '\n') {
    };
    selectedMenu(input, Contacts);
  } while (input != 5);
  db_print(Contacts);
  db_free(Contacts);
  return 0;
}
#include <stdio.h>
#include <string.h>

struct abonent {
  char name[10];
  char second_name[10];
  char tel[10];
};
void pr(struct abonent *abb) { strcpy(abb[1].name, "TEST"); }
void ch(struct abonent *abb) { printf("%s", abb[1].name); }
int main() {
  struct abonent Contacts[100] = {0};

  pr(Contacts);
  ch(Contacts);
}

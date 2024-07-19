#include "contact_manager.h"

void printMenu() {
  printf("------------------------------------------------\n");
  printf("1. Добавить абонента\n");
  printf("2. Удалить абонента\n");
  printf("3. Поиск абонентов по имени\n");
  printf("4. Вывод всех записей\n");
  printf("5. Выход\n");
  printf("------------------------------------------------\n");
}

void selectedMenu(int selectedItem, struct list *list) {
  switch (selectedItem) {
    case 1:
      addUser(list);
      break;
    case 2:
      removeUser(list);
      break;
    case 3:
      searchUser(list);
      break;
    case 4:
      printAllUser(list);
      break;
  }
}
void searchUser(struct list *list) {
  char name[10];
  printf("Введите имя абонента для поиска :");
  inputSting(name);
  system("clear");
  int counterValid = 0;
  for (int i = 0; i < list->count; ++i) {
    struct list_abonent *abonent = get_element(list, i);
    if (strcmp(abonent->name, name) == 0) {
      counterValid++;
      printCurrentUser(*abonent, counterValid);
    }
  }
  printf("Совпадений найдено %d\n", counterValid);
}

void removeUser(struct list *list) {
  char name[10];
  printf("Введите Имя абонента для удаления : ");
  inputSting(name);
  int index_user = db_search_name(list, name);
  if (index_user == -1) {
    system("clear");
    printf("\033[33mПользователь с таким именем не найден\033[0m\n");
  } else {
    db_delete(list, index_user);
  }
}
void inputSting(char *val) {
  scanf("%9s", val);
  while (getchar() != '\n') {
  };
}
void addUser(struct list *list) {
  printf("Введите Имя абонента : ");
  char name[10];
  inputSting(name);
  printf("Введите второе имя абонента : ");
  char second_name[10];
  inputSting(second_name);
  printf("Введите телефон абонента : ");
  char tel[10];
  inputSting(tel);
  db_insert(list, list->count + 1, name, second_name, tel);
}
void printCurrentUser(struct list_abonent list, int i) {
  printf("%d. Name : %s\n", i, list.name);
  printf("   Second name :%s\n", list.second_name);
  printf("   Phone : %s\n", list.tel);
}
void printAllUser(struct list *list) {
  system("clear");
  for (int i = 0; i < list->count; ++i) {
    struct list_abonent *abonent = get_element(list, i);
    printCurrentUser(*abonent, i + 1);
  }
}
int my_strlen(char *arr) {
  int i = 0;
  while (*arr != '\0') {
    arr++;
    i++;
  }
  return i;
}
int checkValidName(char *nameCurrent, char *nameSearch) {
  int valie = 1;
  int len_cur = my_strlen(nameCurrent);
  int len_search = my_strlen(nameSearch);
  if (len_cur != len_search) {
    valie = 0;  // Строки разной длины, не совпадают
  } else {
    while (*nameCurrent != '\0') {
      if (*nameCurrent != *nameSearch) {
        valie = 0;
      }
      nameCurrent++;
      nameSearch++;
    }
  }
  return valie;
}
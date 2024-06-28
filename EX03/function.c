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

void selectedMenu(int selectedItem, struct abonent *abonent) {
  switch (selectedItem) {
    case 1:
      addUser(abonent);
      break;
    case 2:
      /* code */
      break;
    case 3:
      /* code */
      break;
    case 4:
      printAllUser(abonent);
      break;
  }
}

void addUser(struct abonent *abonent) {
  printf("Введите Имя абонента : ");
  char name[10];
  scanf("%s", name);
  printf("Введите второе имя абонента : ");
  char second_name[10];
  scanf("%s", second_name);
  printf("Введите телефон абонента : ");
  char tel[10];
  scanf("%s", tel);

  int index = searchIndexNullAbonent(abonent);
  strcpy(abonent[index].name, name);
  strcpy(abonent[index].second_name, second_name);
  strcpy(abonent[index].tel, tel);
}
int searchIndexNullAbonent(struct abonent *abonent) {
  int index = 0;
  for (int i = 0; i < 100; ++i) {
    if (abonent->name[i] == 0) {
      index = i;
      break;
    }
  }
  return index;
}

void printAllUser(struct abonent *abonent) {
  system("clear");
  for (int i = 0; i < 100; ++i) {
    if (checkValidName(abonent[i].name, "") != 1) {
      printf("%d. Name : %s\n", i + 1, abonent[i].name);
      printf("   Second name :%s\n", abonent[i].second_name);
      printf("   Phone : %s\n", abonent[i].tel);
    }
  }
}
void deletedUser(struct abonent *abonent, char *name) {
  int flag = 0;
  for (int i = 0; i < 100; ++i) {
    if (checkValidName(abonent[i].name, name) == 1) {
      strcpy(abonent[i].name, "");
      strcpy(abonent[i].second_name, "");
      strcpy(abonent[i].tel, "");
      flag = 1;

      break;
    }
  }
  flag == 1 ? printf("Пользователь удален, успешно")
            : printf("Пользователь с таким именем не найден");
}

int checkValidName(char *nameCurrent, char *nameSearch) {
  int valie = 1;
  while (*nameCurrent != '\0') {
    if (*nameCurrent != *nameSearch) {
      valie = 0;
    }
    nameCurrent++;
    nameSearch++;
  }
  return valie;
}
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
      removeUser(abonent);
      break;
    case 3:
      searchUser(abonent);
      break;
    case 4:
      printAllUser(abonent);
      break;
  }
}
void searchUser(struct abonent *abonent) {
  char name[10];
  printf("Введите имя абонента для поиска :");
  inputSting(name);
  system("clear");
  int counterValid = 0;
  for (int i = 0; i < 100; ++i) {
    if (checkValidName(abonent[i].name, name) == 1) {
      counterValid++;
      printCurrentUser(abonent[i], counterValid);
    }
  }
  printf("Совпадений найдено %d\n", counterValid);
}

void removeUser(struct abonent *abonent) {
  char name[10];
  printf("Введите Имя абонента для удаления : ");
  inputSting(name);
  deletedUser(abonent, name);
}
void inputSting(char *val) {
  scanf("%9s", val);
  while (getchar() != '\n') {
  };
}
void addUser(struct abonent *abonent) {
  printf("Введите Имя абонента : ");
  char name[10];
  inputSting(name);
  printf("Введите второе имя абонента : ");
  char second_name[10];
  inputSting(second_name);
  printf("Введите телефон абонента : ");
  char tel[10];
  inputSting(tel);
  int index = searchIndexNullAbonent(abonent);
  if (index == -1) {
    printf("Справочник переполнен, не более 100 записей \n");
  } else {
    strcpy(abonent[index].name, name);
    strcpy(abonent[index].second_name, second_name);
    strcpy(abonent[index].tel, tel);
  }
}
int searchIndexNullAbonent(struct abonent *abonent) {
  int index = -1;
  for (int i = 0; i < 100; ++i) {
    if (0 == my_strlen(abonent[i].name)) {
      index = i;
      break;
    }
  }
  return index;
}

void printCurrentUser(struct abonent abonent, int i) {
  printf("%d. Name : %s\n", i, abonent.name);
  printf("   Second name :%s\n", abonent.second_name);
  printf("   Phone : %s\n", abonent.tel);
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
  system("clear");
  flag == 1 ? printf("Пользователь удален, успешно\n")
            : printf("Пользователь с таким именем не найден\n");
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
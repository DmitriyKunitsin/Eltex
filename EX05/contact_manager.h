#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

struct abonent {
char name[10];
char second_name[10];
char tel[10];
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
void printMenu();
void addUser(struct list *abonent);
int searchIndexNullAbonent(struct list *abonent);
void printAllUser(struct list *abonent);
void printCurrentUser(struct list_abonent abonent, int i);
void searchUser(struct list *abonent);
void removeUser(struct list *abonent);
void deletedUser(struct list *abonent, char *name);
int checkValidName(char *nameCurrent, char *nameSearch);
void selectedMenu(int selectedItem, struct list *abonent);
void inputSting(char* val);
int my_strlen(char* arr);
#endif
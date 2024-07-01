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
void printMenu();
void addUser(struct abonent *abonent);
int searchIndexNullAbonent(struct abonent *abonent);
void printAllUser(struct abonent *abonent);
void printCurrentUser(struct abonent abonent, int i);
void searchUser(struct abonent *abonent);
void removeUser(struct abonent *abonent);
void deletedUser(struct abonent *abonent, char *name);
int checkValidName(char *nameCurrent, char *nameSearch);
void selectedMenu(int selectedItem, struct abonent *abonent);
void inputSting(char* val);
int my_strlen(char* arr);
#endif

#include "struct.h"

struct list *db_created() {
  struct list *lst = (struct list *)malloc(sizeof(struct list));

  lst->count = 0;
  lst->head = NULL;
  lst->prev = NULL;

  return lst;
}
void free_abonent(struct list_abonent *abonent) {
  if (abonent == NULL) {
    return;
  }
  free_abonent(abonent->next);
  free(abonent->name);
  free(abonent->second_name);
  free(abonent->tel);
  free(abonent);
}

void db_free(struct list *lst) {
  if (lst == NULL) {
    return;
  }
  free_abonent(lst->head);
  free(lst);
}
void db_insert(struct list *lst, int index, char *name, char *second_name,
               char *tel) {
  struct list_abonent *base = lst->head;

  struct list_abonent *new_abonent =
      (struct list_abonent *)malloc(sizeof(struct list_abonent));

  new_abonent->name = malloc(sizeof(char) * strlen(name));
  strcpy(new_abonent->name, name);
  new_abonent->second_name = malloc(sizeof(char) * strlen(second_name));
  strcpy(new_abonent->second_name, second_name);
  new_abonent->tel = malloc(sizeof(char) * strlen(tel));
  strcpy(new_abonent->tel, tel);

  if (base == NULL) {
    // Этот элемент единственный, а значит его указатели будут NULL.
    new_abonent->next = NULL;
    new_abonent->prev = NULL;

    // При этом, он сам будет первым и последним в списке.
    lst->head = new_abonent;
    lst->prev = new_abonent;
    lst->count++;  // Увеличем кол-во на единицу

    return;
  }
  // Если индекс, который пришел будет меньше нуля, то будем вставлять в конец
  if (index < 0) {
    // голова теперь будет ссылаться на новый элм. впереди себя
    base->prev = new_abonent;
    new_abonent->prev = NULL;
    new_abonent->next =
        base;  // а ссылка на след. элм. у нового будет на голову

    lst->head = new_abonent;  // новый элемент голова
  } else {
    base = lst->prev;  // в хвост списка

    // ссылаеться на новый элемент
    base->next = new_abonent;
    new_abonent->next = NULL;  // Новый не будет иметь ссылки на следующий
    new_abonent->prev = base;  // А предыдущий у него будет хвост списка

    lst->prev = new_abonent;  // Назначаем новый элемент хвостом списка
  }

  lst->count++;
}

struct list_abonent *get_element(struct list *lst, int index) {
  struct list_abonent *base;
  int middle = lst->count / 2;  // вычиляю середину списка

  if (index > middle) {  // если индекс больше середины
    base = lst->prev;
    for (int i = lst->count; i > lst->count; --i) {
      base = base->prev;
    }
  } else {
    base = lst->head;
    for (int i = 0; i < index; ++i) {
      base = base->next;
    }
  }
  // Если элемента нет
  if (base == NULL) {
    printf("\033[3;31mОшибка! В базе нет данных\n\033[0m");
    return NULL;
  }

  return base;
}

int db_search_name(struct list *lst, char *name) {
  int validName = -1;
  for (int i = 0; i < lst->count; ++i) {
    struct list_abonent *base = get_element(lst, i);  // первый жлемент
    if (strcmp(base->name, name) == 0) {
      validName = i;
    }
  }

  return validName;
}

void db_delete(struct list *lst, int index) {
  struct list_abonent *base = get_element(lst, index);
  struct list_abonent *prev, *next;
  if (base == NULL) return;

  prev = base->prev;  // получение предыдущего элемента
  next = base->next;  // мы получаем следующий элемент

  // переопределение указателя для предыдущего элемента на следующий
  if (prev != NULL) {
    prev->next = base->next;
  }
  if (next != NULL) {
    next->prev = base->prev;
  }

  free(base);
  lst->count--;
}

void db_print(struct list *lst) {
  struct list_abonent *base = get_element(lst, 0);  // переходим к началу списка
  if (base != NULL) {
    puts("\033[36m***Распечатка базы***\033[0m");

    if (lst->count == 0) {  // если список пустой, так и говорим
      printf("Записей в базе нет\n");
      return;
    }

    int i = 0;  // организуем счетчик
    while (base !=
           NULL) {  // Пока все элементы не кончаться мы будем их перебирать
      printf("ID: %d || Имя: %s\n", i, (char *)base->name);  // выводя на экран
      base = base->next;
      i++;
    }
    // В конце покажем какой размер у нашего списка
    printf("\033[36mРазмер базы: %d\033[0m\n", lst->count);
  } else {
    printf("\033[33m База пуста \033[0m");
  }
}

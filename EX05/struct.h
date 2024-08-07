/**
 * @file struct.h
 * @brief Мое жалкое пародие на лист
 * @author Дммитрий Куницин
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Структура конкретного абонента
 */
struct list_abonent {
char *name;
char *second_name;
char *tel;
struct list_abonent *next;
struct list_abonent *prev;
};
/**
 * @brief Структура для записи текущего абонента
 */
struct list
{
    int count;
    struct list_abonent *head;
    struct list_abonent *prev;
};

/**
 * @brief Создание листа для наполнения списка
 */
struct list *db_created();
/**
 * @brief Рекурсивная очистка структура контактов
 */
void free_abonent(struct list_abonent *abonent);
/**
 * @brief Очищение листа
 */
void db_free(struct list *lst);
/**
 * @brief Добавление в листпользователя
 */
void db_insert(struct list *lst, int index, char *name, char *second_name, char *tel);
/**
 * @brief Поиск по индексу пользователя в листе
 * @returns Возвращает указатель на структуру нужного пользователя
 */
struct list_abonent *get_element(struct list *lst, int index);
/**
 * @brief Поиск пользователя по имени в листе
 * @returns Возвращает индекс найденного пользователя, если пользователь не найден вернет -1
 */
int db_search_name(struct list *lst, char *name);
/**
 * @brief Удаление пользователя из листа по индексу
 */
void db_delete(struct list *lst, int index);
/**
 * @brief Вывод всех записей из листа
 */
void db_print(struct list *lst);

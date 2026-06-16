# Абонентский справочник (Contact Manager)

## Описание

Консольное приложение на C для управления списком контактов. Данные хранятся в статическом массиве (макс. 100 записей).

## Структура абонента

struct abonent {
char name[10];
char second_name[10];
char tel[10];
};

## Функции программы

1. Добавить абонента
2. Удалить абонента
3. Поиск по имени
4. Вывод всех записей
5. Выход

## Файлы

- contact_manager.c — точка входа (main)
- contact_manager.h — объявления
- function.c — реализация всех функций

## Сборка

```bash
gcc contact_manager.c function.c -o contact_manager
```

## Запуск

```bash
./contact_manager
```

## Автор

Студент НГУ

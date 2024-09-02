#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>      /// Для printf, perror и других функций ввода-вывода
#include <stdlib.h>     /// Для exit и malloc
#include <string.h>     /// Для работы со строками
#include <fcntl.h>      /// Для O_CREAT и O_RDWR
#include <sys/stat.h>   /// Для mq_attr
#include <mqueue.h>     /// Для работы с очередями сообщений
#include <unistd.h>     /// Для close и других системных вызовов
#include <pthread.h>    /// Для работы с потоками

#include "../client/front.h"

#define REGISTER_COMAND "REGISTER:%s:" ///  Префикс протокола регистрации клиента
#define YOUR_ID_AND_QUEUE "REGID:%d QUEUE:%s" /// Префикс ответа клиенту с его id и очередью
#define QUEUE_NAME_PREFIX "/client_queue_%d" /// Префикс названия очереди зарегистрированного пользователя
#define EXIT_COMAND "exit:" /// ПРотокол выхода клиента
#define EXIT_INPUT "exit"   /// Команда выхода
#define NEW_USER "NEWUSER:%s ID:%d" /// Протокол оповещения о новом пользователе

#define QUEUE_SERVER "/chat_server" /// Название серверного чата

#define MAX_MSG_SIZE 256 /// Максимальный размер сообщения

#define INITIAL_CAPACITY 10

/**
 * Структура пользователя
 */
typedef struct
{
    int id; // Айди
    char user_name[50]; // Имя пользователя
    char queue_name[50]; // Имя очереди для сообщ
    bool is_active; // Статус активности
} User;

/**
 * Структура всех пользователей
 */
typedef struct
{
    User *users; /// Динамический массив пользователей
    size_t count; // Кол-во зарегестриррованный польщователей
    size_t capacity; /// Вместимость массива
    mqd_t mq_server;
} User_Registry;

#endif
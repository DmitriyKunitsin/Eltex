#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

#define QUEUE_SERVER "/chat_server"
#define QUEUE_CLIENT "/chat_client"
#define MAX_MSG_SIZE 256
#define MAX_CLIENTS 18
#define EXIT "exit"

#define EXIT_COMAND "exit:"
#define CLIENT_COMAND "CLIENT:"
#define ALL_COMAND "ALL:"
#define SELECTED_USER "SELECTED:"
#define YOUR_ID "ID:%d"
#define ANSWER_ALL "ID:%dMESSAGE:%s"



#define QUEUE_NAME_PREFIX "/client_queue_"

int  running = 1;

typedef struct {
    int count;
    int id;
    char name[50];
    char text[256];
} message;


typedef struct
{
    mqd_t server_queue; // очередь сервера
    mqd_t client_queue; // очередь клиента
    char name[50]; // имя клиента
    int id; // id клиента
} client_info;

typedef struct {
    char name[50];
    char queue_name[64];// имя очереди клиента
    mqd_t mq_client;// очередь клиента
}Client_info_;

typedef struct {
    mqd_t server_queue; // очередь сервера
    client_info clients[50]; // массив клиентов
    int client_count; // кол-во клиентов
    pthread_mutex_t mutex;// Мьютекс для защиты доступа к массиву клиентов
} server_data;

typedef struct {
    mqd_t mq_server;
    mqd_t mq_client;
    client_info *users;
    message *msg;
} thread_args_t;

mqd_t create_client_queue(const char *client_id) {
    char queue_name[64];
    snprintf(queue_name, sizeof(queue_name), "%s%s", QUEUE_NAME_PREFIX, client_id);
    printf("queue_name : %s\n", queue_name);
    // Создаем очередь с уникальным именем
    mqd_t mq_client = mq_open(queue_name, O_CREAT | O_RDWR, 0644, NULL);
    if (mq_client == (mqd_t)-1) {
        perror("mq_open ошибка создания очереди при регистрации");
        return -1;
    }
    return mq_client;
}

void *service_chatt(void *arg) {
    server_data *data = (server_data *)arg;

    message msg;


    while(running) {
        ssize_t size_msg = mq_receive(data->server_queue, msg.text, MAX_MSG_SIZE, NULL);
        if(0 <= size_msg) {

            msg.text[size_msg] = '\0';

            pthread_mutex_lock(&data->mutex);
            if(strncmp(msg.text, CLIENT_COMAND, 7) == 0) { // регистрация клиента
                char *name = strtok(msg.text, ":");
                name = strtok(NULL, ":"); // имя клиента
                if(name != NULL && data->client_count < MAX_CLIENTS) {
                    strncpy(data->clients[data->client_count].name, name, sizeof(data->clients[data->client_count].name) - 1);
                    data->clients[data->client_count].name[sizeof(data->clients[data->client_count].name) - 1] = '\0';
                    data->clients[data->client_count].id = data->client_count + 1;// ID

                    char register_msg[256];
                    sprintf(register_msg, sizeof(register_msg), YOUR_ID, data->clients[data->client_count].id);


                    // Отправка сообщения клиенту
                    if(mq_send(data->clients[data->client_count].server_queue, register_msg, strlen(register_msg) + 1, 1) == -1) {
                        printf("Пользователя %s не удалось подключить к чату\n", data->clients[data->client_count].name);
                    }

                    printf("Пользователь %s подключился к чату\n", data->clients[data->client_count].name);
                    /**
                     * TODO отправить всем пользователям, что подключился пользователь и обновить экран пользователей
                     */
                    data->client_count++;
                } else {
                    printf("Пользователя %s пытался подключиться к чату, но лимит пользователей превышен\n", name);
                }
            } else if(strstr(msg.text, EXIT_COMAND) != NULL) { // Выход клиента
                    char *message = strtok(msg.text, ":");
                    char *id_str = strtok(NULL, ":"); //  ID клиента
                    char *client_name = strtok(NULL, ":");//  имя клиента 
                    int client_id = atoi(id_str);
                    for(int i = 0; i < data->client_count; ++i) {
                        if(data->clients[i].id == client_id) {
                            printf("Пользователь %s (ID : %d)вышел из чата\n", data->clients[i].name, client_id);
                            data->clients[i] = data->clients[--data->client_count];
                            /**
                             * TODO отправить всем пользователям, что отключился пользователь и обновить экран пользователей
                             */
                            break;
                        }
                    }
            } else if (strncmp(msg.text, ALL_COMAND, 4) == 0) { // Широковещательное сообщение
                for (int i = 0; i < data->client_count; i++) {
                    mq_send(data->clients[i].client_queue, msg.text + 4, strlen(msg.text + 4) + 1, 1);
                }
            } else if (strncmp(msg.text, SELECTED_USER, 9) == 0) { // Личное сообщение
                char *token = strtok(msg.text + 9, ":");
                int recipient_id = atoi(token);
                token = strtok(NULL, ":");

                for (int i = 0; i < data->client_count; i++) {
                    if (data->clients[i].id == recipient_id) {
                        mq_send(data->clients[i].client_queue, token, strlen(token) + 1, 1);
                        break;
                    }
                }
            }
            pthread_mutex_unlock(&data->mutex);
        }
    }

    return NULL;
}

void *service_chat(void *arg) {
    thread_args_t *args_th = (thread_args_t *)arg;

    message msg;
    msg.id = 0;
    msg.count = 0;
    printf("Сервер запущен. Ожидание сообщений...\n");

    while (running == 1) {
        ssize_t size_msg = mq_receive(args_th->mq_server, msg.text, MAX_MSG_SIZE, NULL);
        if (0 <= size_msg) {
                msg.text[size_msg] = '\0';
            
            if (strncmp(msg.text, CLIENT_COMAND, 7) == 0) { // если от клиента, то регистрация
                char *token = strtok(msg.text, ":");
                token = strtok(NULL, ":"); // достаем имя клиента
                if (token != NULL) {
                    strncpy(msg.name, token, 50 - 1);
                    msg.name[sizeof(msg.name) - 1] = '\0'; // Завершаем строку
                    msg.id += 1;
                    msg.count += 1;
                    char register_msg[256]; 
                    char id[10];
                    snprintf(id, sizeof(id), "%d", msg.id);
                    create_client_queue(id);
                    snprintf(register_msg, sizeof(register_msg), YOUR_ID, msg.id);

                    if (mq_send(args_th->mq_server, register_msg, strlen(register_msg) + 1, 1) == -1) {
                        perror("mq_send register");
                    }
                    printf("Пользователь %s подключился к чату\n", msg.name);
                    /**
                     * TODO добавление в бд пользователя
                     */
                }
            } else {

                if (strstr(msg.text, EXIT_COMAND) != NULL) {
                    char *message = strtok(msg.text, ":");
                    char *id_str = strtok(NULL, ":"); //  ID клиента
                    char *client_name = strtok(NULL, ":");//  имя клиента 

                    if (id_str != NULL && client_name != NULL) {
                        int client_id = atoi(id_str); 
                        printf("Пользователь %s (ID: %d) вышел из чата\n", client_name, client_id);
                        /**
                         * TODO удаление из бд пользователя и его id
                         */
                        msg.count -= 1; 
                    } else {
                        printf("Ошибка парсинга сообщения о выходе.\n");
                    }
                }
                // обычное сообщение
                else if (strncmp(msg.text, ALL_COMAND, 4) == 0) { // широковещательный пакет
                    char *all = strtok(msg.text, "ALL:");
                    char *name_token = strtok(NULL, "NAME:"); //  имя пользователя
                    char *id_token = strtok(NULL, "ID:"); // ID пользователя
                    char *message_token = strtok(NULL, "MESSAGE:"); // сообщение пользователя

                    if (name_token != NULL && id_token != NULL && message_token != NULL) {
                        strncpy(msg.name, name_token, 50);
                        msg.name[sizeof(msg.name) - 1] = '\0'; // конец строки
                        msg.id = atoi(id_token);
                        
                        printf("Получено сообщение от %s (ID: %d): %s\n", msg.name, msg.id, message_token);
                        for(int i = 0; i < msg.id; ++i) {
                            char answer[256];
                            snprintf(answer, sizeof(answer), ANSWER_ALL, i, msg.text);
                            mq_send(args_th->mq_client, answer, strlen(answer) + 1, 1);
                        }
                    } else {
                        printf("Ошибка парсинга сообщения.\n");
                    }
                }

            printf("Всего пользователей: %d\n", msg.count);   

            }
                // char *search_ex = strstr(msg.text, EXIT);
                if (running == 0) {
                    break;
                }
        }
    }
    
    printf("Сервер отключен...\n");
    return NULL;

}
int main() {
    mqd_t mq, mq_chat;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 1024;  // Максимальное количество сообщений в очереди
    attr.mq_msgsize = MAX_MSG_SIZE;  // Максимальный размер сообщения
    attr.mq_curmsgs = 0;  // Текущее количество сообщений в очереди

    mq = mq_open(QUEUE_SERVER, O_CREAT | O_RDWR, 0666 ,&attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open Серверу не удалось создать и запустить серверную очередь");
        exit(EXIT_FAILURE);
    }

    mq_chat = mq_open(QUEUE_CLIENT, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open Серверу не удалось создать и запустить клиентскую очередь");
        exit(EXIT_FAILURE);
    }
    pthread_t pthread_chat;
    thread_args_t args_chat;
    args_chat.mq_server = mq;
    args_chat.mq_client = mq_chat;

    if(pthread_create(&pthread_chat, NULL, service_chat, &args_chat) != 0) {//запуск потока для обслуживания чата
        perror("Ошибка создания потока чтения чата");
        mq_close(mq);
        return EXIT_FAILURE;
    }
    
    char input_serv[50];
    while (1) {
        printf("Введите команду: exit для отключения \n");
        fgets(input_serv, sizeof(input_serv), stdin);
        input_serv[strcspn(input_serv, "\n")] = 0; 

        if (strcmp(input_serv, EXIT) == 0) {
            printf("Завершение работы сервера...\n");
            running = 0;
            printf("running : %d\n", running);
            break;
        }
    }


    pthread_join(pthread_chat, NULL);
    mq_close(mq);
    mq_unlink(QUEUE_SERVER);
    return 0;
}
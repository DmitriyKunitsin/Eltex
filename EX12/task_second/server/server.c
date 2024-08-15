#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_NAME "/chat_queue"
#define MAX_MSG_SIZE 256
#define EXIT "exit"

typedef struct {
    int count;
    int id;
    char name[50];
    char text[256];
} message;

void *print_chat(void *arg) {
    mqd_t mq = *((mqd_t *)arg);
    message msg;
    msg.id = 0;
    printf("Сервер запущен. Ожидание сообщений...\n");

    while (1) {
        ssize_t size_msg = mq_receive(mq, msg.text, MAX_MSG_SIZE, NULL);
        if (0 <= size_msg) {
                msg.text[size_msg] = '\0';
            
            if (strncmp(msg.text, "CLIENT:", 7) == 0) { // если от клиента, то регистрация
                char *token = strtok(msg.text, ":");
                token = strtok(NULL, ":"); // достаем имя клиента
                if (token != NULL) {
                    strncpy(msg.name, token, 50 - 1);
                    msg.name[sizeof(msg.name) - 1] = '\0'; // Завершаем строку
                    msg.id += 1;
                    printf("Пользователь %s подключился к чату\n", msg.name);
                }
            } else {

                printf("Всего пользователей %d : %s \n", msg.id,msg.text);
            }
                char *search_ex = strstr(msg.text, EXIT);
                if (search_ex != NULL) {
                    break;
                }
        }
    }
    
    printf("Сервер отключен...\n");
    return NULL;

}
int main() {
    mqd_t mq;
    struct mq_attr attr;

    // Настройка атрибутов очереди
    attr.mq_flags = 0;
    attr.mq_maxmsg = 1024;  // Максимальное количество сообщений в очереди
    attr.mq_msgsize = MAX_MSG_SIZE;  // Максимальный размер сообщения
    attr.mq_curmsgs = 0;  // Текущее количество сообщений в очереди

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666 ,&attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open Серверу не удалось создать и запустить очередь");
        exit(EXIT_FAILURE);
    }
    pthread_t pthread_chat;

    if(pthread_create(&pthread_chat, NULL, print_chat, &mq) != 0) {//запуск потока для чтения чата
        perror("Ошибка создания потока чтения чата");
        mq_close(mq);
        return EXIT_FAILURE;
    }

    pthread_join(pthread_chat, NULL); // Дождаться завершения потока перед выходом
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

/*
    message msg;
    msg.id = 0;
    printf("Сервер запущен. Ожидание сообщений...\n");

    while (1) {
        ssize_t size_msg = mq_receive(mq, msg.text, MAX_MSG_SIZE, NULL);
        if (0 <= size_msg) {
                msg.text[size_msg] = '\0';
            
            if (strncmp(msg.text, "CLIENT:", 7) == 0) { // если от клиента, то регистрация
                char *token = strtok(msg.text, ":");
                token = strtok(NULL, ":"); // достаем имя клиента
                if (token != NULL) {
                    strncpy(msg.name, token, 50 - 1);
                    msg.name[sizeof(msg.name) - 1] = '\0'; // Завершаем строку
                    msg.id += 1;
                    printf("Пользователь %s подключился к чату\n", msg.name);
                }
            } else {

                printf("Всего пользователей %d : %s \n", msg.id,msg.text);
            }
                char *search_ex = strstr(msg.text, EXIT);
                if (search_ex != NULL) {
                    break;
                }
        }
    }
    
    printf("Сервер отключен...\n");
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

*/
    return 0;
}
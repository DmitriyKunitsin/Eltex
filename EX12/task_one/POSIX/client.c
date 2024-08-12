#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_NAME "/my_queue"
#define MAX_SIZE 1024

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];

    mq = mq_open(QUEUE_NAME, O_RDWR);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    const char *message = "CLIENT: Hello!";
    mq_send(mq, message, strlen(message) + 1, 0);

    while (1) {
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read >= 0) {
            buffer[bytes_read] = '\0';
            if (strncmp(buffer, "SERVER:", 7) == 0) {
                printf("%s\n", buffer);
                break;
            }
        } else {
            perror("mq_receive");
        }
    }

    // сообщение для выхода
    const char *exit_message = "CLIENT: exit";
    mq_send(mq, exit_message, strlen(exit_message) + 1, 0);

    mq_close(mq);

    return 0;
}

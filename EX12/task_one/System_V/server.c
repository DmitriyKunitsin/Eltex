#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_KEY 1234

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    int msgid;
    struct msg_buffer message;

    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    message.msg_type = 1;
    strcpy(message.msg_text, "Hi!");
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0);
    printf("Сообщение от клиента: %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

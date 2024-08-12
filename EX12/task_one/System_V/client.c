#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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

    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
    printf("Сообщение от сервера: %s\n", message.msg_text);

    message.msg_type = 2;
    strcpy(message.msg_text, "Hello!");
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    return 0;
}

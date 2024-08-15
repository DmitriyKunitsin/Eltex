#ifndef CLIENT_H_
#define CLIENT_H_

#include <fcntl.h>
#include <mqueue.h>
#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "front.h"
#include "utils.h"






typedef struct {
    mqd_t mq;
    WINDOW *chat_win;
    Chat_state *state;
} thread_args_t;

typedef struct {
    int count;
    int id;
    char name[50];
    char text[256];
} message;


#endif
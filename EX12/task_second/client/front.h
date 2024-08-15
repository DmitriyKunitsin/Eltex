#ifndef FRONT_H_
#define FRONT_H_

#include <ncurses.h>
#include "utils.h"

typedef struct {
    char chat[MAX_CHAT_LINES][MAX_MSG_LENGTH];
    char users[MAX_USERS][50];
    int chat_line_count;
    int user_count;
} Chat_state;


void init_windows(WINDOW **chat_win, WINDOW **user_win, WINDOW **input_win);

void display_chat(Chat_state *state,WINDOW *chat_win);

void display_users(Chat_state *state,WINDOW *user_win);

void add_chat_message(Chat_state *state,const char *msg);

void add_user(Chat_state *state,const char *username);

#endif
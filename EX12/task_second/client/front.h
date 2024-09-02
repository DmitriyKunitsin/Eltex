
#include <ncurses.h>

#include <mqueue.h>

// #define MAX_USERS 10
// #define MAX_CHAT_LINES 18
// #define MAX_MSG_LENGTH 256
// #define QUEUE_NAME "/chat_test"
// #define EXIT "exit"

// char chat[MAX_CHAT_LINES][MAX_MSG_LENGTH];
// char users[MAX_USERS][50];
// int chat_line_count = 0;
// int user_count = 0;

// typedef struct {
//     mqd_t mq;
//     WINDOW *chat_win;
// } thread_args_t;


void init_windows(WINDOW **chat_win, WINDOW **user_win, WINDOW **input_win);
void display_chat(WINDOW *chat_win);
void display_users(WINDOW *user_win);

void add_chat_message(const char *msg);

// void add_user(const char *username);
// void registration_message(char name[50], mqd_t mq, WINDOW *input_chat);

void *print_chat(void *arg);
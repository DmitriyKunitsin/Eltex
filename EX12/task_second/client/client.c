#include "client.h"



void registration_message(Chat_state *state, char name[50], mqd_t mq, WINDOW *input_chat) {
    display_chat(state,input_chat);

    mvwprintw(input_chat, 1, 1, "Whats is your name: ");
    wrefresh(input_chat);

    wgetnstr(input_chat, name, 50 - 1);

    add_chat_message(state,name);
    display_chat(state,input_chat);
    werase(input_chat);
    wrefresh(input_chat);

    name[strcspn(name, "\n")] = '\0';
    int len_register_name = strlen(name);
    char register_msg[len_register_name + 8];
    snprintf(register_msg, sizeof(register_msg), "CLIENT:%s:", name);
    if (mq_send(mq, register_msg, strlen(register_msg) + 1, 1) == -1) {
        perror("mq_send");
    }
}

void *print_chat(void *arg) {
    thread_args_t *thread_args = (thread_args_t *)arg;
    mqd_t mq = thread_args->mq;
    WINDOW *chat_win = thread_args->chat_win;
    Chat_state *state = &thread_args->state;
    message msg;
    while (1) {
        ssize_t size_msg = mq_receive(mq, msg.text, MAX_MSG_LENGTH, NULL);
        if (0 <= size_msg) {
            msg.text[size_msg] = '\0';
                add_chat_message(state,msg.text);
                display_chat(state,chat_win);
            char *search_ex = strstr(msg.text, EXIT);
            if (search_ex != NULL) {
                break;
            }
        }
    }
    return NULL;
}
int main() {
    WINDOW *chat_win, *user_win, *input_win;
    char input_msg[MAX_MSG_LENGTH];

    initscr();  // Инициализация ncurses
    cbreak();   // Включение режима "разбивки"
    keypad(stdscr, TRUE);  // Включение поддержки клавиш F1 и стрелок

    Chat_state state = { .chat_line_count = 0, .user_count = 0};

    init_windows(&chat_win, &user_win, &input_win);

    display_chat(&state,chat_win);
    display_users(&state,user_win);

    /**
     * Рабоча с очередью
     */
    mqd_t mq;

    mq = mq_open(QUEUE_NAME, O_RDWR);
    if (mq == (mqd_t)-1) {
        perror("mq_open ошибка открытия для чтения");
        exit(EXIT_FAILURE);
    }
    // message msg;
    char name[50];
    registration_message(&state,name, mq, input_win);

    pthread_t pthread_reciever_chat;
    thread_args_t args_chat;
    args_chat.mq = mq;
    args_chat.chat_win = chat_win;
    args_chat.state = &state;
    
    if (pthread_create(&pthread_reciever_chat, NULL, print_chat, &args_chat) != 0) {
        perror("Ошибка создания потока чтения чата");
        mq_close(mq);
        return EXIT_FAILURE;
    }
    ///////////////////////////////////////////////////////////////////////////
    while (1) {
        box(input_win, 0, 0);  // Рисуем рамку
        mvwprintw(input_win, 1, 1, "Set message: ");
        wrefresh(input_win);

        wgetnstr(input_win, input_msg, MAX_MSG_LENGTH - 1);

        if (strcmp(input_msg, EXIT) == 0) {
            break;
        }
        if (mq_send(mq, input_msg, strlen(input_msg) + 1, 1) == -1) {
        perror("mq_send не удалось отправить сообщение 195 строчка");
        }
        // add_chat_message(input_msg);
        // display_chat(chat_win);
        werase(input_win);  // Очистка окна ввода
        wrefresh(input_win);
    }

    delwin(chat_win);
    delwin(user_win);
    delwin(input_win);
    endwin();  // Завершение работы ncurses

    return 0;
}

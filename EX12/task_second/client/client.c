#include "client.h"
int main() {
    WINDOW *chat_win, *user_win, *input_win;
    char input_msg[MAX_MSG_SIZE];

    initscr();  // Инициализация ncurses
    cbreak();   // Включение режима "разбивки"
    keypad(stdscr, TRUE); 

    init_windows(&chat_win, &user_win, &input_win);

    display_chat(chat_win);
    display_users(user_win);

    mqd_t mq_server = mq_open(QUEUE_SERVER, O_RDWR);
    if (mq_server == (mqd_t) - 1) {
        perror("mq_open ошибка открытия серверной очереди");
        exit(EXIT_FAILURE);
    }



    User user;
    user.id = registration_message(user.user_name,user.queue_name,mq_server, input_win);


    mqd_t my_queue = mq_open(user.queue_name, O_RDWR);
    if (mq_server == (mqd_t)-1) {
        perror("mq_open ошибка открытия своей очереди");
        exit(EXIT_FAILURE);
    }
    /// TODO Поток обновления чата

    /// TODO Поток обновления людей онлайн
    while (1) {
        box(input_win, 0, 0);  // Рисуем рамку
        mvwprintw(input_win, 1, 1, "Set message: ");
        wrefresh(input_win);

        wgetnstr(input_win, input_msg, MAX_MSG_SIZE - 1);

        if (strcmp(input_msg, EXIT_INPUT) == 0) {
            user.user_name[strcspn(user.user_name, "\n")] = '\0';
            int len_register_name = strlen(user.user_name);
            char exit_msg[len_register_name + 10];
            snprintf(exit_msg, sizeof(exit_msg), "exit:%d:%s", user.id,user.user_name);
            if(mq_send(mq_server, exit_msg, strlen(exit_msg) + 1, 1) == - 1) {
                perror("mq_send не удалось отправить сообщение выхода");
            } else {
                break;
            }
        }
    }
    
    delwin(chat_win);
    delwin(user_win);
    delwin(input_win);
    endwin();
    return 0;
}

int registration_message(char name[50],char user_queue_name[50], mqd_t mq_server, WINDOW *input_chat) {
    display_chat(input_chat);

    mvwprintw(input_chat, 1, 1, "Whats is your name: ");
    wrefresh(input_chat);

    wgetnstr(input_chat, name, 50 - 1);

    add_chat_message(name);
    display_chat(input_chat);
    werase(input_chat);
    wrefresh(input_chat);

    name[strcspn(name, "\n")] = '\0';
    int len_register_name = strlen(name);
    char register_msg[len_register_name + 11];
    snprintf(register_msg, sizeof(register_msg), REGISTER_COMAND , name);
    if (mq_send(mq_server, register_msg, strlen(register_msg) + 1, 1) == -1) {
        perror("mq_send");
    }
    char receiver[MAX_MSG_SIZE];
    ssize_t size_msg = mq_receive(mq_server, receiver, MAX_MSG_SIZE, NULL);
    
    if (0 <= size_msg) {
        if (strncmp(receiver, "REGID:", 6) == 0)  {
            char *id = strtok(receiver, ":");
            id = strtok(NULL, ":");// id после REGID:
            if (id != NULL) {
                receiver[size_msg] = '\0';
                int my_id = atoi(id);// в инт

                char *queue_name = strtok(NULL, ":");// имя очереди после QUEUE:
                if (queue_name != NULL) {
                    // printf("Имя очереди : %s, длина : %d\n", queue_name, strlen(queue_name));
                    strncpy(user_queue_name, queue_name, strlen(queue_name));
                    return my_id;
                }
            }
        } else {
            fprintf(stderr, "Неудалось подключиться к серверу.\nНекорректный ответ от сервера: %s\n", receiver);
            return -1; 
        }
    } else {
        perror("mq_receive");
        return -1; 
    }
}

#include "client.h"


mqd_t create_client_queue(const char *client_id) {
    char queue_name[64];
    snprintf(queue_name, sizeof(queue_name), "%s%s", QUEUE_NAME_PREFIX, client_id);
    
    
    mqd_t mq_client = mq_open(queue_name, O_RDWR);
    if (mq_client == (mqd_t)-1) {
        perror("mq_open не удалось открыть очередь клиента queue_name ");
        printf("queue_name %s\n", queue_name);
        printf("id : %s\n", client_id);
        return -1;
    }
    return mq_client;
}
int registration_message(Chat_state *state, char name[50], mqd_t mq_server, WINDOW *input_chat) {
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
    if (mq_send(mq_server, register_msg, strlen(register_msg) + 1, 1) == -1) {
        perror("mq_send register");
    }
     // Ожидание ответа от сервера
    char response[256]; 
    ssize_t bytes_received = mq_receive(mq_server, response, sizeof(response), NULL);
    
    if (bytes_received >= 0) {
        response[bytes_received] = '\0'; // Завершаю строку
        if (strncmp(response, "ID:", 3) == 0) {
            int my_id = atoi(response + 3); //  ID
            
            return my_id; // ID клиента
        } else {
            fprintf(stderr, "Неудалось подключиться к серверу.\nНекорректный ответ от сервера: %s\n", response);
            return -1; // Обработка некорректного ответа
        }
    } else {
        perror("mq_receive");
        return -1; // Обработка ошибки
    }
}

void *print_chat(void *arg) {
    thread_args_t *thread_args = (thread_args_t *)arg;
    mqd_t mq_server = thread_args->mq;
    WINDOW *chat_win = thread_args->chat_win;
    Chat_state *state = &thread_args->state;
    message *msg = &thread_args->msg;
    while (1) {
        ssize_t size_msg = mq_receive(mq_server, msg->text, MAX_MSG_LENGTH, NULL);
        if (0 <= size_msg) {
                add_chat_message(state,msg->text);
                display_chat(state,chat_win);
            if(strncmp(msg->text, ANSWER_ALL, 17) == 0) {
                char *baff_msg = strtok(msg->text,  ANSWER_ALL);
                msg->text[size_msg] = '\0';
                add_chat_message(state,msg->text);
                display_chat(state,chat_win);
            char *search_ex = strstr(msg->text, EXIT);
            if (search_ex != NULL) {
                break;
            }
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
    keypad(stdscr, TRUE); 

    Chat_state state = { .chat_line_count = 0, .user_count = 0};

    init_windows(&chat_win, &user_win, &input_win);

    display_chat(&state,chat_win);
    display_users(&state,user_win);

    /**
     * Рабоча с очередью
     */
    mqd_t mq_server, mq_client;

    mq_server = mq_open(QUEUE_SERVER, O_RDWR);
    if (mq_server == (mqd_t)-1) {
        perror("mq_open ошибка открытия серверной очереди");
        exit(EXIT_FAILURE);
    }
    // mq_client = mq_open(QUEUE_CLIENT, O_RDWR);
    // if (mq_client == (mqd_t)-1) {
    //     perror("mq_open ошибка открытия клиентской очереди");
    //     exit(EXIT_FAILURE);
    // }
    message msg;
    char name[50];
    msg.my_id = registration_message(&state,name, mq_server, input_win);
    if(-1 == msg.my_id) {
        perror("Ошибка регистрации");
        exit(EXIT_FAILURE);
    }
    char id[10];
    snprintf(id, sizeof(id), "%d", msg.my_id);
    mq_client = create_client_queue(id);
    strncpy(msg.name, name, 50);
    pthread_t pthread_reciever_chat;
    thread_args_t args_chat;
    args_chat.mq = mq_client;
    args_chat.chat_win = chat_win;
    args_chat.state = &state;
    args_chat.msg =  &msg;
    
    if (pthread_create(&pthread_reciever_chat, NULL, print_chat, &args_chat) != 0) {
        perror("Ошибка создания потока чтения чата");
        mq_close(mq_client);
        return EXIT_FAILURE;
    }
    ///////////////////////////////////////////////////////////////////////////
    while (1) {
        box(input_win, 0, 0);  // Рисуем рамку
        mvwprintw(input_win, 1, 1, "Set message: ");
        wrefresh(input_win);

        wgetnstr(input_win, input_msg, MAX_MSG_LENGTH - 1);

        if (strcmp(input_msg, EXIT) == 0) {
            name[strcspn(name, "\n")] = '\0';
            int len_register_name = strlen(name);
            char exit_msg[len_register_name + 10];
            snprintf(exit_msg, sizeof(exit_msg), "exit:%d:%s", msg.my_id,name);
            if(mq_send(mq_server, exit_msg, strlen(exit_msg) + 1, 1) == - 1) {
                perror("mq_send не удалось отправить сообщение выхода");
            } else {
                break;
            }
        }
        input_msg[strcspn(input_msg, "\n")] = '\0'; 

        char formatted_msg[MAX_MSG_LENGTH]; //  буфер для форматированного сообщения
        snprintf(formatted_msg, sizeof(formatted_msg), "ALL:NAME:%s:ID%d:MESSAGE:%s", msg.name, msg.my_id, input_msg);

        if (mq_send(mq_server, formatted_msg, strlen(formatted_msg) + 1, 1) == -1) {
            perror("mq_send не удалось отправить сообщение");
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

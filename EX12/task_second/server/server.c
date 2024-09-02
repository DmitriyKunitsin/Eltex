#include "server.h"

int running = 1;

int main(void) {
    User_Registry reg;
    init_user_registry(&reg);

    mqd_t mq;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 1024;  // Максимальное количество сообщений в очереди
    attr.mq_msgsize = MAX_MSG_SIZE;  // Максимальный размер сообщения
    attr.mq_curmsgs = 0;  // Текущее количество сообщений в очереди

    mq = mq_open(QUEUE_SERVER, O_CREAT | O_RDWR, 0666 ,&attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open Серверу не удалось создать и запустить серверную очередь");
        exit(EXIT_FAILURE);
    }
    reg.mq_server = mq;
    pthread_t chat_thread;

    if (pthread_create(&chat_thread, NULL, chat_function, (void*)&reg) != 0) {
        perror("Не удалось создать поток для чата");
        exit(EXIT_FAILURE);
    }

    while (1) {

       char input_text[MAX_MSG_SIZE];
       scanf("%s", input_text);

        if (strcmp(input_text, EXIT_INPUT) == 0) {
            if(mq_send(mq, EXIT_INPUT, strlen(EXIT_INPUT), NULL)) {
                perror("mq_send не удалось отправить сообщение выхода");
            } else {
                running = 0;
                break;
            }
        }

        if(strstr(input_text, "allon") != NULL) {
            int online = 0;
                for(size_t i = 0; i < reg.count; ++i) {
                    if(reg.users[i].is_active  == true) {
                        printf("name : %s, id : %d, queue : %s\n",reg.users[i].user_name, reg.users[i].id, reg.users[i].queue_name);
                        online++;
                }
            }
            printf("All users online : %d:\n", online);
        }
        if (strstr(input_text, "alloff") != NULL) {
            printf("All users %d:\n", reg.count);
                for(size_t i = 0; i < reg.count; ++i) {
                    printf("name : %s, id : %d, queue : %s\n",reg.users[i].user_name, reg.users[i].id, reg.users[i].queue_name);
            }
        }

    }
    pthread_join(chat_thread, NULL); // Ожидание завершения потока

    mq_close(mq);
    mq_unlink(QUEUE_SERVER);
    
    return 0;
}


/**
 * Инициализация реестра пользователей
 */
void init_user_registry(User_Registry *reg) {
    reg->count = 0;
    reg->capacity = INITIAL_CAPACITY;
    reg->users = malloc(reg->capacity * sizeof(User));
}
/**
 * 
 */
void resize_user_registry(User_Registry *reg) {
    reg->capacity *= 2;
    reg->users = realloc(reg->users, reg->capacity * sizeof(User));
    if (!reg->users) {
        perror("Не удалось перераспределить память");
        exit(EXIT_FAILURE);
    }
}

/**
 * Регистрация пользователя
 * @param reg Структура данных пользователей
 * @param user_name Имя нового пользователя
 * @returns Возвращает ID вновь зарегистрированного пользователя
 */
int add_user(User_Registry *reg, const char *user_name) {
    if(reg->count >= reg->capacity) {
        resize_user_registry(reg);
    }

    User new_user;
    new_user.id = reg->count;
    strncpy(new_user.user_name, user_name, sizeof(new_user.user_name));

    snprintf(new_user.queue_name, sizeof(new_user.queue_name), QUEUE_NAME_PREFIX, new_user.id);
    printf("new user id : %d, queueu_name :%s, user_name : %s\n", new_user.id, new_user.queue_name, new_user.user_name);
    reg->users[reg->count].is_active = true;
    reg->users[reg->count++] = new_user;
    return new_user.id;
}
/**
 * Выход пользователей
 * @param reg Структура данных всех пользователей
 * @param id ID пользователя
 * Находит пользователя по уникальному ID  и вешает ему статус Не активен
 */
void exit_user(User_Registry *reg, const int id) {
    for(size_t i = 0; i < reg->count; ++i) {
        if(reg->users[i].id == id) {
            reg->users[i].is_active = false;
            break;
        }
    }
}
/**
 * Освобождение памяти
 */
void free_user_regisrty(User_Registry *reg) {
    free(reg->users);
    mq_close(reg->mq_server);
}

/**
 * Поиск пользователя по ID и Name
 * @param reg Массив зарегестрированных пользователей
 * @param id Id пользователя для поиска
 * @param user_name Name пользователя для поиска
 * @returns Если пользователь не найден, то возвращает NULL, иначе возвращает нужного пользователя
 */
User* find_user(User_Registry *reg, const int id, const char*user_name) {
    for(size_t i = 0; i < reg->count; ++i) {
        if(reg->users[i].id ==  id) {
            if(strcmp(reg->users[i].user_name, user_name) == 0) {
                return &reg->users[i];
            }
        }
    }
    return NULL;
}
/**
 * Создание клиентской очереди с уникальным именем,
 * префикс стандартный + постфикс ID пользователя
 * @param client_id ID пользователя, используется как постфикс к имени очереди
 * @returns Возвращает созданную очередь mqd_t mq_client
 */
mqd_t create_client_queue(const int client_id) {
    char queue_name[64];
    snprintf(queue_name, sizeof(queue_name), QUEUE_NAME_PREFIX, client_id);
    // printf("queue_name : %s\n", queue_name);
    
    mqd_t mq_client = mq_open(queue_name, O_CREAT | O_RDWR, 0666, NULL);
    if (mq_client == (mqd_t)-1) {
        perror("mq_open ошибка создания очереди при регистрации");
        return -1;
    }
    return mq_client;
}
void *chat_function(void* arg) {
    // TODO логика обработки сервисного чата
    User_Registry *reg = (User_Registry *)arg;

    mqd_t mq_server = reg->mq_server;
    char text[MAX_MSG_SIZE];

    printf("Сервер запущен. Ожидание сообщений...\n");
    while( running ) {
        ssize_t size_msg = mq_receive(mq_server, text, MAX_MSG_SIZE, NULL);
        if (0 <= size_msg) {
            text[size_msg] = '\0';
            if(0 == strncmp(text, REGISTER_COMAND, 9)) { /// Регистрация
                printf("text : %s\n", text);
                char *token = strtok(text, ":");
                token = strtok(NULL, ":");  /// достаю имя
                printf("name : %s\n", token);
                if( token != NULL) {
                    int id = add_user(reg, token);
                    mqd_t client_queue =  create_client_queue(id);
                    if (client_queue == (mqd_t)-1) {
                        continue; 
                    }
                    char register_msg[256]; 
                    snprintf(register_msg, sizeof(register_msg),YOUR_ID_AND_QUEUE, id, reg->users[id].queue_name);
                    printf("\n%s\n", register_msg);
                    if (mq_send(mq_server, register_msg, strlen(register_msg) + 1, 1) == -1) {
                        perror("mq_send register");
                    }
                    printf("Пользователь %s подключился к чату\n", reg->users[id].user_name);
                    /// TODO оповестить всех, что подключился новый пользователь
                    for(size_t i = 0; i < reg->count; ++i) {
                        if(reg->users[i].is_active == true) {
                            if (mq_send(reg->users[i].queue_name, "NEWUSER:%s ID:%d", reg->users[id].queue_name, id) == -1) {
                                perror("mq_send не удалось оповестить пользователя  о новом пользователе");
                            }
                        }
                    }
                }
            } else {

                if(strstr(text, EXIT_COMAND) != NULL) {
                    char *message = strtok(text, ":");
                    char *id_str = strtok(NULL,  ":");
                    char *client_name = strtok(NULL, ":");

                    if(id_str !=  NULL && client_name != NULL) {
                        int client_id = atoi(id_str);
                        printf("Пользователь %s (ID: %d) вышел из чата\n", client_name, client_id);
                        User_Registry *cur_user = find_user(reg, client_id, client_name);
                        if (cur_user != NULL) {
                            exit_user(reg, client_id);
                        }
                    }
                }
            }
        }
    }
}
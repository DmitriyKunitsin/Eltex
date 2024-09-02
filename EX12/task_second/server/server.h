#include "../util/util.h"
/**
 * Инициализация реестра пользователей
 */
void init_user_registry(User_Registry *reg);
/**
 * 
 */
void resize_user_registry(User_Registry *reg);

/**
 * Регистрация пользователя
 * @param reg Структура данных пользователей
 * @param user_name Имя нового пользователя
 * @returns Возвращает ID вновь зарегистрированного пользователя
 */
int add_user(User_Registry *reg, const char *user_name);
/**
 * Выход пользователей
 * @param reg Структура данных всех пользователей
 * @param id ID пользователя
 * Находит пользователя по уникальному ID  и вешает ему статус Не активен
 */
void exit_user(User_Registry *reg, const int id);
/**
 * Освобождение памяти
 */
void free_user_regisrty(User_Registry *reg);

/**
 * Поиск пользователя по ID и Name
 * @param reg Массив зарегестрированных пользователей
 * @param id Id пользователя для поиска
 * @param user_name Name пользователя для поиска
 * @returns Если пользователь не найден, то возвращает NULL, иначе возвращает нужного пользователя
 */
User* find_user(User_Registry *reg, const int id, const char*user_name);
/**
 * Создание клиентской очереди с уникальным именем,
 * префикс стандартный + постфикс ID пользователя
 * @param client_id ID пользователя, используется как постфикс к имени очереди
 * @returns Возвращает созданную очередь mqd_t mq_client
 */
mqd_t create_client_queue(const int client_id);
void *chat_function(void* arg);
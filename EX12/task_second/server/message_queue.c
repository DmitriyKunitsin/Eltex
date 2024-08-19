#include "message_queue.h"

mqd_t create_client_queue(const char *client_name) {
    char queue_name[64];
    snprintf(queue_name, sizeof(queue_name), "%s%s", QUEUE_NAME_PREFIX, client_name);
    
    // Создаем очередь с уникальным именем
    mqd_t mq_client = mq_open(queue_name, O_CREAT | O_RDWR, 0644, NULL);
    if (mq_client == (mqd_t)-1) {
        perror("mq_open");
        return -1;
    }
    return mq_client;
}
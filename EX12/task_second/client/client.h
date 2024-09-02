#ifndef CLIENT_H_
#define CLIENT_H_

#include "../util/util.h"

int registration_message(char name[50],char user_queue_name[50], mqd_t mq_server, WINDOW *input_chat);


#endif
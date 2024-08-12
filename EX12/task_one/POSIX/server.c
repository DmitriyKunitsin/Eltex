#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_NAME "/my_queue"
#define MAX_SIZE 1024

int main() {
  mqd_t mq;
  char buffer[MAX_SIZE];
  struct mq_attr attr;

  // атрибуты очереди
  attr.mq_flags = 0; // режим работы очереди
  attr.mq_maxmsg = 10; // Максимальное количество сообщений в очереди
  attr.mq_msgsize = MAX_SIZE; // Максимальный размер сообщения
  attr.mq_curmsgs = 0;  // текущее колличество сообщений в очереди

  mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
  if (mq == (mqd_t)-1) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  while (1) {
    ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
    if (bytes_read >= 0) {
      buffer[bytes_read] = '\0'; 

      if (strncmp(buffer, "CLIENT:", 7) == 0) {
        printf("%s\n", buffer);
        const char *message = "SERVER: Hi!";
        mq_send(mq, message, strlen(message) + 1, 0);
      } else {
        printf("Сообщение не от клиента.\n");
      }

      if (strcmp(buffer, "CLIENT: exit") == 0) {
        break;
      }
    } else {
      perror("mq_receive");
    }
  }

  mq_close(mq);
  mq_unlink(QUEUE_NAME);

  return 0;
}

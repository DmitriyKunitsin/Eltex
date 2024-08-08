#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *fifoName = "server/my_fifo";


    if (mkfifo(fifoName, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    
    int fd = open(fifoName, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }


    const char *message = "Hi!";
    write(fd, message, strlen(message) + 1);


    close(fd);


    unlink(fifoName);

    return 0;
}

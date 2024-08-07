#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *fifoName = "../server/my_fifo";
    
    int fd = open(fifoName, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("Received: %s\n", buffer);
    } else {
        printf("No data received.\n");
    }
    
    close(fd);

    unlink(fifoName);

    return 0;
}

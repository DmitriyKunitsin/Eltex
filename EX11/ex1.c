#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    // неименованный канал
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // дочерний процесс
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Родительский процесс
        close(pipefd[0]);

        const char *message = "Hi!";
        write(pipefd[1], message, strlen(message)  + 1);

        close(pipefd[1]);
        wait(NULL); 
    } else { // Дочерний процесс
        close(pipefd[1]);

        read(pipefd[0], buffer, sizeof(buffer));
        printf("Дочерний процесс прочитал: %s\n", buffer);

        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

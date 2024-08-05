#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Дочерний процесс: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(1);
    } else {
        int status;
        printf("Родительский процесс: PID = %d, PPID = %d\n", getpid(), getppid());
        
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Дочерний процесс завершился с кодом: %d\n", WEXITSTATUS(status));
        } else {
            printf("Дочерний процесс завершился ненормально\n");
        }
    }

    return 0;
}

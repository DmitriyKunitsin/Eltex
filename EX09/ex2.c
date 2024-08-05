#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void create_processes() {
    pid_t pid1, pid2, pid3, pid4, pid5;

    pid1 = fork();
    if (pid1 < 0) {
        perror("Ошибка при создании процесса 1");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        printf("Процесс 1: PID = %d, PPID = %d\n", getpid(), getppid());

        pid3 = fork();
        if (pid3 < 0) {
            perror("Ошибка при создании процесса 3");
            exit(EXIT_FAILURE);
        } else if (pid3 == 0) {
            printf("Процесс 3: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        }

        pid4 = fork();
        if (pid4 < 0) {
            perror("Ошибка при создании процесса 4");
            exit(EXIT_FAILURE);
        } else if (pid4 == 0) {
            printf("Процесс 4: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        }

        waitpid(pid3, NULL, 0);
        waitpid(pid4, NULL, 0);
        exit(0); 
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Ошибка при создании процесса 2");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        printf("Процесс 2: PID = %d, PPID = %d\n", getpid(), getppid());

        pid5 = fork();
        if (pid5 < 0) {
            perror("Ошибка при создании процесса 5");
            exit(EXIT_FAILURE);
        } else if (pid5 == 0) {
            printf("Процесс 5: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        }

        waitpid(pid5, NULL, 0);
        exit(0); 
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return;
}

int main() {
    create_processes();
    return 0;
}

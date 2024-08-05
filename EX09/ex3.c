#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARG_LEN 100

void execute_command(char *command) {
    char *args[MAX_ARG_LEN];
    pid_t pid;
    int status;

    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARG_LEN - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid = fork();
    if (pid < 0) {
        perror("Ошибка при создании процесса");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("Ошибка execvp");
        exit(EXIT_FAILURE);
    } else {
        do {
            waitpid(pid, &status, 0);
        } while (!WIFEXITED(status));
    }
}

int main() {
    char command[MAX_CMD_LEN];

    printf("Добро пожаловать в простой командный интерпретатор!\n");
    printf("Введите 'exit' для выхода.\n");

    while (1) {
        printf("> "); 
        if (fgets(command, MAX_CMD_LEN, stdin) == NULL) {
            perror("Ошибка ввода");
            continue;
        }

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_command(command);
    }

    printf("Выход из интерпретатора.\n");
    return 0;
}

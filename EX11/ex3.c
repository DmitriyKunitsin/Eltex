#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARG_LEN 100
#define MAX_CMDS 10

void execute_command(char *command) {
    char *commands[MAX_CMDS];
    int num_commands = 0;

    commands[num_commands++] = strtok(command, "|");
    while ((commands[num_commands] = strtok(NULL, "|")) != NULL && num_commands < MAX_CMDS - 1) {
        num_commands++;
    }
    commands[num_commands] = NULL;

    int pipefd[2 * (num_commands - 1)];
    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipefd + i * 2) == -1) {
            perror("Ошибка создания пайпа");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_commands; i++) {
        char *args[MAX_ARG_LEN];
        char *token = strtok(commands[i], " ");
        int j = 0;

        while (token != NULL && j < MAX_ARG_LEN - 1) {
            args[j++] = token;
            token = strtok(NULL, " ");
        }
        args[j] = NULL;

        pid_t pid = fork();
        if (pid < 0) {
            perror("Ошибка при создании процесса");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { 
            if (i > 0) {
                if (dup2(pipefd[(i - 1) * 2], STDIN_FILENO) == -1) {
                    perror("Ошибка dup2");
                    exit(EXIT_FAILURE);
                }
            }
            if (i < num_commands - 1) { 
                if (dup2(pipefd[i * 2 + 1], STDOUT_FILENO) == -1) {
                    perror("Ошибка dup2");
                    exit(EXIT_FAILURE);
                }
            }

            for (int k = 0; k < 2 * (num_commands - 1); k++) {
                close(pipefd[k]);
            }

            execvp(args[0], args);
            perror("Ошибка execvp");
            exit(EXIT_FAILURE);
        }
    }


    for (int i = 0; i < 2 * (num_commands - 1); i++) {
        close(pipefd[i]);
    }

    for (int i = 0; i < num_commands; i++) {
        wait(NULL); 
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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

void check_error(bool expression, char* message) {
    if (expression) {
        write(STDOUT_FILENO, message, strlen(message) * sizeof(char));
        write(STDOUT_FILENO, "\n", 1);
        exit(-1);
    }
}

int main (int argc, char* argv[]) {
    pid_t pid;  // id процесса
    int pipe_1[2];  // arr для дескрипт.
    if (pipe(pipe_1) == -1) {
        perror("pipe");
        _exit(EXIT_FAILURE);
    }
    if (argc != 2) {
        write(1, "Ошибка: неправильно переданы аргументы!\n", 42);
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    check_error(fd == -1, "Ошибка: файл не открывается!");
    pid = fork();  // создаём дочку
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        close(pipe_1[0]);
        check_error(dup2(fd, STDIN_FILENO) < 0, "Ошибка дублирования!");
        dup2(pipe_1[1], STDOUT_FILENO);
        execl("./child", "/.child", NULL);
        perror("Ошибка: execl!");
        return 1;
    }
    else {
        check_error((pid == -1), "Ошибка процесса!");
        close(pipe_1[1]);
        wait(0);
        int result;
        char answer[50];
        while ((read(pipe_1[0], &result, sizeof(int))) > 0) {
            if (result == -1) {
                write(STDOUT_FILENO, "Произошла какая-то ошибка...\n", 22);
                return 1;
            }
            sprintf(answer, "%d\n", result);
            check_error(write(STDOUT_FILENO, answer, strlen(answer)) == -1, "Ошибка вывода!\n");
            check_error(write(STDOUT_FILENO, "\n", 1) == -1, "Ошибка вывода!\n");
        }
    }
    return 0;
}

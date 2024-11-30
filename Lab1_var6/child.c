#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#define buf_size 100

int main() {
    char buffer[buf_size];
    int result = 0;
    int count = 0;
    while (read(STDIN_FILENO, buffer + count, 1) > 0) {
        if (buffer[count] == '\n' || buffer[count] == EOF) {
            buffer[count] = '\0';
            int number;
            char *token = strtok(buffer, " ");
            while (token != NULL) {
                if (sscanf(token, "%d", &number) == 1) {
                    result += number;
                }
                token = strtok(NULL, " ");
            }
            write(STDOUT_FILENO, &result, sizeof(result));
            result = 0;
            count = 0;
        } else {
            count++;
        }
    }
    return 0;
}

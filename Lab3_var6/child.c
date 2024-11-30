#include <stdio.h>
#include <unistd.h>  // write read close STDOUT_FILENO
#include <stdlib.h>  // exit
#include <sys/mman.h>  // mmap munmap shm_open
#include <sys/types.h>  // типы данных и структуры для файлов и процессов
#include <sys/wait.h>
#include <sys/stat.h>  // типы данных и структуры для файлов и процессов
#include "stddef.h"
#include <fcntl.h>  //  управление файлами shm_open).
#include <string.h>
#include <stdbool.h>


#define MEMORY_NAME "LR3"  
#define DATA_SIZE 256
#define MEMORY_SIZE 8192

void check_error(bool expression, char* message) {
    if (expression) {
        write(STDOUT_FILENO, message, strlen(message) * sizeof(char));
        write(STDOUT_FILENO, "\n", 1);
        exit(-1);
    }
}

typedef struct {
    size_t size;
    int data[DATA_SIZE];
} res;

int main() {
    int fd = shm_open(MEMORY_NAME, O_RDWR, S_IRUSR | S_IWUSR);
    check_error(fd == -1, "Can't open shared memory file");
    if (ftruncate(fd, MEMORY_SIZE) == -1) {
        printf("File is too large");
    }
    res *addr = mmap(NULL, MEMORY_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    check_error(addr == (void*)-1, "Mmap error");
    addr->size = 0;

    char c;
    bool not_end = true;
    int nmbr = 0;
    int result = 0;
    int count = 0;
    int numbers[100];

    do {
        if (not_end) {
            if (c <= '9' && c >= '0') {
                nmbr = nmbr * 10 + c - '0';
            }
            if (c == ' ' || c == '\n' || c == EOF) {
                numbers[count] = nmbr;
                nmbr = 0;
                count++;
                if (c == '\n' || c == EOF) {
                    for (int i = 0; i < count; i++) {
                        result = result + numbers[i];
                    }
                    not_end = false;
                    count = 0;
                }
            }
        }
        if (c == '\n' || c == EOF) {
            addr->data[addr->size++] = result;
            result = 0;
            not_end = true;
        }
    } while((scanf("%c", &c)) > 0);

    return 0;
}
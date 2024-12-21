#include <stdio.h>
#include "method1.h"  // линковка на этапе компиляции

int main() {
    float A, B, e, deltaX;
    int command;

    printf("Введите команду: ");
    while (scanf("%d", &command) && command != -1) {
        if (command == 1) {
            printf("Введите A, B, e: ");
            scanf("%f %f %f", &A, &B, &e);
            printf("Результат: %.6f\n", SinIntegral(A, B, e));
        } else if (command == 2) {
            printf("Введите A, deltaX: ");
            scanf("%f %f", &A, &deltaX);
            printf("Результат: %.6f\n", Derivative(A, deltaX));
        } else {
            printf("Неизвестная команда!\n");
        }
        printf("Введите команду: ");
    }

    return 0;
}

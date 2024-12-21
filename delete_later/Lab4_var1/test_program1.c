#include <stdio.h>
#include "math_library.h"

int main() {
    float A, B, e, deltaX;
    int command;

    printf("Введите команду (1 или 2): ");
    while (scanf("%d", &command) != EOF) {
        if (command == 1) {
            printf("Введите A, B и e: ");
            scanf("%f %f %f", &A, &B, &e);
            printf("Результат SinIntegral: %f\n", SinIntegral(A, B, e));
        } else if (command == 2) {
            printf("Введите A и deltaX: ");
            scanf("%f %f", &A, &deltaX);
            printf("Результат Derivative: %f\n", Derivative(A, deltaX));
        } else {
            printf("Неверная команда.\n");
        }
        printf("Введите команду (1 или 2): ");
    }

    return 0;
}

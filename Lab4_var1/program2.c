#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

typedef float (*FuncSinIntegral)(float, float, float);
typedef float (*FuncDerivative)(float, float);

int main() {
    void *handle = NULL;
    FuncSinIntegral SinIntegral = NULL;
    FuncDerivative Derivative = NULL;
    char libPath[256];
    int command;

    printf("Введите путь к библиотеке: ");
    scanf("%s", libPath);

    handle = dlopen(libPath, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    SinIntegral = (FuncSinIntegral)dlsym(handle, "SinIntegral");
    Derivative = (FuncDerivative)dlsym(handle, "Derivative");
    if (!SinIntegral || !Derivative) {
        fprintf(stderr, "Ошибка загрузки функций: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    printf("Введите команду: ");
    while (scanf("%d", &command) && command != -1) {
        if (command == 1) {
            float A, B, e;
            printf("Введите A, B, e: ");
            scanf("%f %f %f", &A, &B, &e);
            printf("Результат: %.6f\n", SinIntegral(A, B, e));
        } else if (command == 2) {
            float A, deltaX;
            printf("Введите A, deltaX: ");
            scanf("%f %f", &A, &deltaX);
            printf("Результат: %.6f\n", Derivative(A, deltaX));
        } else if (command == 0) {
            printf("Введите путь к новой библиотеке: ");
            scanf("%s", libPath);

            dlclose(handle);
            handle = dlopen(libPath, RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
                return 1;
            }

            SinIntegral = (FuncSinIntegral)dlsym(handle, "SinIntegral");
            Derivative = (FuncDerivative)dlsym(handle, "Derivative");
            if (!SinIntegral || !Derivative) {
                fprintf(stderr, "Ошибка загрузки функций: %s\n", dlerror());
                dlclose(handle);
                return 1;
            }
        } else {
            printf("Неизвестная команда!\n");
        }
        printf("Введите команду: ");
    }

    dlclose(handle);
    return 0;
}

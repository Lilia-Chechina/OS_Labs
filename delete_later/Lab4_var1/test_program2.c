#include <stdio.h>
#include <dlfcn.h>

typedef float (*SinIntegralFunc)(float, float, float);
typedef float (*DerivativeFunc)(float, float);

int main() {
    char *libPaths[] = {"./libmath_rect.so", "./libmath_trap.so"};
    int currentLib = 0;
    void *handle = dlopen(libPaths[currentLib], RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    SinIntegralFunc SinIntegral = (SinIntegralFunc)dlsym(handle, "SinIntegral");
    DerivativeFunc Derivative = (DerivativeFunc)dlsym(handle, "Derivative");

    char command;
    float A, B, e, deltaX;

    printf("Введите команду (0 для переключения библиотеки, 1 или 2): ");
    while (scanf(" %c", &command) != EOF) {
        if (command == '0') {
            dlclose(handle);
            currentLib = 1 - currentLib;
            handle = dlopen(libPaths[currentLib], RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
                return 1;
            }
            SinIntegral = (SinIntegralFunc)dlsym(handle, "SinIntegral");
            Derivative = (DerivativeFunc)dlsym(handle, "Derivative");
            printf("Библиотека переключена на %s\n", libPaths[currentLib]);
        } else if (command == '1') {
            printf("Введите A, B и e: ");
            scanf("%f %f %f", &A, &B, &e);
            printf("Результат SinIntegral: %f\n", SinIntegral(A, B, e));
        } else if (command == '2') {
            printf("Введите A и deltaX: ");
            scanf("%f %f", &A, &deltaX);
            printf("Результат Derivative: %f\n", Derivative(A, deltaX));
        } else {
            printf("Неверная команда.\n");
        }
        printf("Введите команду (0 для переключения библиотеки, 1 или 2): ");
    }

    dlclose(handle);
    return 0;
}

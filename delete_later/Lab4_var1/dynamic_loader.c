#include <stdio.h>
#include <dlfcn.h>

// Определяем типы функций
typedef float (*SinIntegralFunc)(float, float, float);
typedef float (*DerivativeFunc)(float, float);

int main() {
    // Загружаем библиотеку
    void *handle = dlopen("./libmath.dylib", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка при загрузке библиотеки: %s\n", dlerror());
        return 1;
    }

    // Получаем указатели на функции
    SinIntegralFunc SinIntegral = (SinIntegralFunc)dlsym(handle, "SinIntegral");
    DerivativeFunc Derivative = (DerivativeFunc)dlsym(handle, "Derivative");

    // Проверяем наличие ошибок
    char *error;
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Ошибка при загрузке функции: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Вызываем функции
    float result1 = SinIntegral(0, 3.14, 0.01);
    printf("Результат SinIntegral(0, 3.14, 0.01): %f\n", result1);

    float result2 = Derivative(0, 0.01);
    printf("Результат Derivative(0, 0.01): %f\n", result2);

    // Закрываем библиотеку
    dlclose(handle);
    return 0;
}

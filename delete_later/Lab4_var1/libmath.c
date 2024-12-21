#include <math.h>

// Реализация функции SinIntegral
float SinIntegral(float A, float B, float e) {
    float sum = 0.0;
    for (float x = A; x < B; x += e) {
        sum += sinf(x) * e;
    }
    return sum;
}

// Реализация функции Derivative
float Derivative(float A, float deltaX) {
    return (cosf(A + deltaX) - cosf(A)) / deltaX;
}

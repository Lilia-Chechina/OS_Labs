#include <math.h>
#include "math_library.h"

// Интеграл методом трапеций
float SinIntegral(float A, float B, float e) {
    float sum = 0.0;
    for (float x = A; x < B; x += e) {
        sum += (sinf(x) + sinf(x + e)) * e / 2;
    }
    return sum;
}

// Производная центральной разностью
float Derivative(float A, float deltaX) {
    return (cosf(A + deltaX) - cosf(A - deltaX)) / (2 * deltaX);
}

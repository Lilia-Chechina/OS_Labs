#include <math.h>

// Метод трапеций
float SinIntegral(float A, float B, float e) {
    float result = 0.0;
    for (float x = A; x < B; x += e) {
        result += (sin(x) + sin(x + e)) * e / 2; 
    }
    return result;
}

// Центральная разность
float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}

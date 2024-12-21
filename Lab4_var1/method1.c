#include <math.h>

// Метод прямоугольников
float SinIntegral(float A, float B, float e) {
    float result = 0.0;
    for (float x = A; x < B; x += e) {
        result += sin(x) * e; 
    }
    return result;
}

// Односторонняя разность
float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A)) / deltaX; 
}

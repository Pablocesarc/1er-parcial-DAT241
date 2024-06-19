
#include <stdio.h>

float suma(float *num1, float *num2) {
    return *num1 + *num2;
}

float resta(float *num1, float *num2) {
    return *num1 - *num2;
}

float multiplicacion(float *num1, float *num2) {
    float resultado = 0;
    for (int i = 0; i < (int)(*num2); i++) {
        resultado = suma(&resultado, num1);
    }
    return resultado;
}

float division(float *num1, float *num2) {
    float resultado = 0;
    float temp_num1 = *num1;
    
    while (temp_num1 >= *num2) {
        temp_num1 = resta(&temp_num1, num2);
        resultado ++;
    }
    
    return resultado;
}

void main() {
    float num1, num2;
    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);

    printf("Suma: %.2f\n", suma(&num1, &num2));
    printf("Resta: %.2f\n", resta(&num1, &num2));
    printf("Multiplicación: %.2f\n", multiplicacion(&num1, &num2));
    printf("División: %.2f\n", division(&num1, &num2));
}

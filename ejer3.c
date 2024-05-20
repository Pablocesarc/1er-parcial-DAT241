#include <stdio.h>
#include <omp.h>


float division(float num1, float num2) {
    int resultado = 0;
    float temp_num1 = num1;
    while (temp_num1 >= num2) {
        temp_num1 -= num2;
        resultado++;
    }
    return resultado;
}

void main() {
    float num1, num2;
    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);

    // Multiplicación
    float mult_result = 0;
    #pragma omp parallel for reduction(+:mult_result)
    for (int i = 0; i < (int)num2; i++) {
        mult_result += num1;
    }
    printf("Multiplicación: %.2f\n", mult_result);

    // División
    float res2 = 0;
    #pragma omp parallel
    {
        float res = division(num1, num2);
        #pragma omp critical
        {
            res2 = res;
        }
    }
    printf("División: %.2f\n", res2);
}

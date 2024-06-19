#include <stdio.h>
#include <omp.h>

// Función de suma
float suma(float *num1, float *num2) {
    return *num1 + *num2;
}

// Función de resta
float resta(float *num1, float *num2) {
    return *num1 - *num2;
}

// Función de multiplicación utilizando sumas y OpenMP
float multiplicacion(float *num1, float *num2) {
    float resultado = 0;
    #pragma omp parallel for reduction(+:resultado)
    for (int i = 0; i < (int)*num2; i++) {
        resultado = suma(&resultado, num1);
    }
    return resultado;
}

// Función de división utilizando restas y OpenMP
float division(float *num1, float *num2) {
    float resultado = 0;
    float temp_num1 = *num1;
    #pragma omp parallel
    {
        float temp_resultado = 0;
        while (temp_num1 >= *num2) {
            temp_num1 = resta(&temp_num1, num2);
            temp_resultado++;
        }
        #pragma omp critical
        {
            resultado += temp_resultado;
        }
    }
    return resultado;
}

int main() {
    float num1 = 9.0;
    float num2 = 3.0;

    // Realizar multiplicación y división utilizando las funciones definidas
    float resultado_mult = multiplicacion(&num1, &num2);
    float resultado_div = division(&num1, &num2);

    printf("Resultado de la multiplicacion: %.2f\n", resultado_mult);
    printf("Resultado de la division: %.2f\n", resultado_div);

    return 0;
}

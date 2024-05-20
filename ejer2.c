#include <iostream>

float suma(float *num1, float *num2) {
    return *num1 + *num2;
}

float resta(float *num1, float *num2) {
    return *num1 - *num2;
}

float multiplicacion(float *num1, float *num2) {
    float resultado = 0;
    for (int i = 0; i < static_cast<int>(*num2); i++) {
        resultado += *num1;
    }
    return resultado;
}

float division(float *num1, float *num2) {
    float resultado = 0;
    float temp_num1 = *num1;
    while (temp_num1 >= *num2) {
        temp_num1 -= *num2;
        resultado++;
    }
    return resultado;
}

int main() {
    float num1, num2;
    std::cout << "Ingrese el primer número: ";
    std::cin >> num1;
    std::cout << "Ingrese el segundo número: ";
    std::cin >> num2;

    std::cout << "Suma: " << suma(&num1, &num2) << std::endl;
    std::cout << "Resta: " << resta(&num1, &num2) << std::endl;
    std::cout << "Multiplicación: " << multiplicacion(&num1, &num2) << std::endl;
    std::cout << "División: " << division(&num1, &num2) << std::endl;

    return 0;
}

#include <stdio.h>
#include "poly.h"

int main() {
    poly_t p1, p2, p_sum;
    // p1 = 1.0 + 2.0*x + 3.0*x^2
    double coeffs1[] = {1.0, 2.0, 3.0}; 
    // p2 = 4.0 + 5.0*x
    double coeffs2[] = {4.0, 5.0};
    double result;

    printf("Запуск С-тестов...\n");

    // Инициализация
    poly_create(&p1, 2, coeffs1);
    poly_create(&p2, 1, coeffs2);

    // Тест 1: Оценка многочлена p1 в точке x=2.0
    poly_eval(&p1, 2.0, &result);
    printf("p1(2.0) = %.2f (Ожидается: 17.00)\n", result);

    // Тест 2: Сложение многочленов
    if (poly_add(&p1, &p2, &p_sum) == POLY_SUCCESS) {
        printf("Сложение успешно. Степень суммы: %zu\n", p_sum.degree);
        poly_eval(&p_sum, 1.0, &result); // (1+2+3) + (4+5) = 15
        printf("p_sum(1.0) = %.2f (Ожидается: 15.00)\n", result);
        poly_free(&p_sum);
    }

    // Освобождение памяти
    poly_free(&p1);
    poly_free(&p2);

    printf("С-тесты завершены.\n");
    return 0;
}

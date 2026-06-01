#ifndef POLY_H
#define POLY_H

#include <stddef.h>

/**
 * @brief Коды возврата функций библиотеки
 */
typedef enum {
    POLY_SUCCESS = 0,           /**< Успешное выполнение */
    POLY_ERR_NULL_PTR = -1,     /**< Передан NULL указатель */
    POLY_ERR_ALLOC = -2,        /**< Ошибка выделения памяти */
    POLY_ERR_INVALID_ARG = -3   /**< Некорректный аргумент */
} poly_err_t;

/**
 * @brief Структура многочлена
 */
typedef struct {
    double *coeffs; /**< Массив коэффициентов, где coeffs[i] - коэффициент при x^i */
    size_t degree;  /**< Степень многочлена */
} poly_t;

/**
 * @brief Создает новый многочлен заданной степени
 * @param p Указатель на структуру многочлена для инициализации
 * @param degree Степень многочлена
 * @param coeffs Массив коэффициентов размера (degree + 1). Если NULL, заполняется нулями.
 * @return Код ошибки
 */
poly_err_t poly_create(poly_t *p, size_t degree, const double *coeffs);

/**
 * @brief Освобождает память, выделенную под многочлен
 * @param p Указатель на многочлен
 */
void poly_free(poly_t *p);

/**
 * @brief Вычисляет значение многочлена в заданной точке x
 * @param p Указатель на многочлен
 * @param x Точка вычисления
 * @param result Указатель для записи результата
 * @return Код ошибки
 */
poly_err_t poly_eval(const poly_t *p, double x, double *result);

/**
 * @brief Складывает два многочлена: res = p1 + p2
 * @param p1 Первый многочлен
 * @param p2 Второй многочлен
 * @param res Результирующий многочлен (память выделяется внутри)
 * @return Код ошибки
 */
poly_err_t poly_add(const poly_t *p1, const poly_t *p2, poly_t *res);

/**
 * @brief Вычитает один многочлен из другого: res = p1 - p2
 * @param p1 Уменьшаемое
 * @param p2 Вычитаемое
 * @param res Результирующий многочлен (память выделяется внутри)
 * @return Код ошибки
 */
poly_err_t poly_sub(const poly_t *p1, const poly_t *p2, poly_t *res);

/**
 * @brief Умножает многочлен на скаляр: res = p * scalar
 * @param p Исходный многочлен
 * @param scalar Скалярное значение
 * @param res Результирующий многочлен
 * @return Код ошибки
 */
poly_err_t poly_mul_scalar(const poly_t *p, double scalar, poly_t *res);

/**
 * @brief Вычисляет производную многочлена
 * @param p Исходный многочлен
 * @param res Многочлен-производная (степень на 1 меньше)
 * @return Код ошибки
 */
poly_err_t poly_derivative(const poly_t *p, poly_t *res);

#endif // POLY_H

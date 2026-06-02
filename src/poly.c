#include "poly.h"
#include <stdlib.h>
#include <string.h>

poly_err_t poly_create(poly_t *p, size_t degree, const double *coeffs) {
    if (!p) return POLY_ERR_NULL_PTR;
    
    p->degree = degree;
    p->coeffs = (double *)calloc(degree + 1, sizeof(double));
    if (!p->coeffs) return POLY_ERR_ALLOC;

    if (coeffs) {
        memcpy(p->coeffs, coeffs, (degree + 1) * sizeof(double));
    }
    return POLY_SUCCESS;
}

void poly_free(poly_t *p) {
    if (p && p->coeffs) {
        free(p->coeffs);
        p->coeffs = NULL;
        p->degree = 0;
    }
}

poly_err_t poly_eval(const poly_t *p, double x, double *result) {
    if (!p || !p->coeffs || !result) return POLY_ERR_NULL_PTR;

    double res = 0.0;
    double x_pow = 1.0;
    for (size_t i = 0; i <= p->degree; i++) {
        res += p->coeffs[i] * x_pow;
        x_pow *= x;
    }
    *result = res;
    return POLY_SUCCESS;
}

static size_t max_size(size_t a, size_t b) {
    return (a > b) ? a : b;
}

poly_err_t poly_add(const poly_t *p1, const poly_t *p2, poly_t *res) {
    if (!p1 || !p2 || !res) return POLY_ERR_NULL_PTR;

    size_t max_deg = max_size(p1->degree, p2->degree);
    poly_err_t err = poly_create(res, max_deg, NULL);
    if (err != POLY_SUCCESS) return err;

    for (size_t i = 0; i <= max_deg; i++) {
        double c1 = (i <= p1->degree) ? p1->coeffs[i] : 0.0;
        double c2 = (i <= p2->degree) ? p2->coeffs[i] : 0.0;
        res->coeffs[i] = c1 + c2;
    }
    return POLY_SUCCESS;
}

poly_err_t poly_sub(const poly_t *p1, const poly_t *p2, poly_t *res) {
    if (!p1 || !p2 || !res) return POLY_ERR_NULL_PTR;

    size_t max_deg = max_size(p1->degree, p2->degree);
    poly_err_t err = poly_create(res, max_deg, NULL);
    if (err != POLY_SUCCESS) return err;

    for (size_t i = 0; i <= max_deg; i++) {
        double c1 = (i <= p1->degree) ? p1->coeffs[i] : 0.0;
        double c2 = (i <= p2->degree) ? p2->coeffs[i] : 0.0;
        res->coeffs[i] = c1 - c2;
    }
    return POLY_SUCCESS;
}

poly_err_t poly_mul_scalar(const poly_t *p, double scalar, poly_t *res) {
    if (!p || !res) return POLY_ERR_NULL_PTR;

    poly_err_t err = poly_create(res, p->degree, NULL);
    if (err != POLY_SUCCESS) return err;

    for (size_t i = 0; i <= p->degree; i++) {
        res->coeffs[i] = p->coeffs[i] * scalar;
    }
    return POLY_SUCCESS;
}

poly_err_t poly_derivative(const poly_t *p, poly_t *res) {
    if (!p || !res) return POLY_ERR_NULL_PTR;

    if (p->degree == 0) {
        return poly_create(res, 0, NULL);
    }

    poly_err_t err = poly_create(res, p->degree - 1, NULL);
    if (err != POLY_SUCCESS) return err;

    for (size_t i = 1; i <= p->degree; i++) {
        res->coeffs[i - 1] = p->coeffs[i] * i;
    }
    return POLY_SUCCESS;
}

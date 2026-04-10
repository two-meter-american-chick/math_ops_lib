#include "math_ops.h"
#include "mo_common.h"

int mo_matrix_multiply_2x2(const double *a, const double *b, double *result) {
    if (a == NULL || b == NULL || result == NULL) {
        return MO_ERR_NULL_PTR;
    }

    result[0] = a[0] * b[0] + a[1] * b[2];
    result[1] = a[0] * b[1] + a[1] * b[3];
    result[2] = a[2] * b[0] + a[3] * b[2];
    result[3] = a[2] * b[1] + a[3] * b[3];

    return MO_OK;
}

int mo_matrix_multiply_3x3(const double *a, const double *b, double *result) {
    double temp[9];
    int i;
    int j;
    int k;

    if (a == NULL || b == NULL || result == NULL) {
        return MO_ERR_NULL_PTR;
    }

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            double sum = 0.0;
            for (k = 0; k < 3; ++k) {
                sum += a[i * 3 + k] * b[k * 3 + j];
            }
            temp[i * 3 + j] = sum;
        }
    }

    for (i = 0; i < 9; ++i) {
        result[i] = temp[i];
    }

    return MO_OK;
}

int mo_matrix_determinant_3x3(const double *m, double *result) {
    double det;

    if (m == NULL || result == NULL) {
        return MO_ERR_NULL_PTR;
    }

    det = m[0] * (m[4] * m[8] - m[5] * m[7])
        - m[1] * (m[3] * m[8] - m[5] * m[6])
        + m[2] * (m[3] * m[7] - m[4] * m[6]);

    *result = det;
    return MO_OK;
}

int mo_matrix_inverse_2x2(const double *m, double *result) {
    double det;
    double inv_det;

    if (m == NULL || result == NULL) {
        return MO_ERR_NULL_PTR;
    }

    det = m[0] * m[3] - m[1] * m[2];
    if (mo_is_near_zero(det)) {
        return MO_ERR_INVALID_ARG;
    }

    inv_det = 1.0 / det;
    result[0] = m[3] * inv_det;
    result[1] = -m[1] * inv_det;
    result[2] = -m[2] * inv_det;
    result[3] = m[0] * inv_det;

    return MO_OK;
}

int mo_solve_linear_2x2(const double *a, const double *b, double *x) {
    double det;

    if (a == NULL || b == NULL || x == NULL) {
        return MO_ERR_NULL_PTR;
    }

    det = a[0] * a[3] - a[1] * a[2];
    if (mo_is_near_zero(det)) {
        return MO_ERR_INVALID_ARG;
    }

    x[0] = (b[0] * a[3] - a[1] * b[1]) / det;
    x[1] = (a[0] * b[1] - b[0] * a[2]) / det;

    return MO_OK;
}

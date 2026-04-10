#include "math_ops.h"
#include "mo_common.h"

#include <stdlib.h>

int mo_matrix_alloc(size_t rows, size_t cols, double **out_ptr) {
    size_t count;
    size_t bytes;
    int rc;

    if (out_ptr == NULL) {
        return MO_ERR_NULL_PTR;
    }

    *out_ptr = NULL;

    rc = mo_matrix_element_count(rows, cols, &count);
    if (rc != MO_OK) {
        return rc;
    }

    if (count > ((size_t)-1) / sizeof(double)) {
        return MO_ERR_OVERFLOW;
    }
    bytes = count * sizeof(double);

    *out_ptr = (double *)calloc(1, bytes);
    if (*out_ptr == NULL) {
        return MO_ERR_ALLOC;
    }

    return MO_OK;
}

int mo_matrix_free(double *ptr) {
    free(ptr);
    return MO_OK;
}

int mo_matrix_fill(double *ptr, size_t rows, size_t cols, double value) {
    size_t i;
    size_t count;
    int rc;

    rc = mo_validate_matrix_ptr(ptr, rows, cols);
    if (rc != MO_OK) {
        return rc;
    }

    rc = mo_matrix_element_count(rows, cols, &count);
    if (rc != MO_OK) {
        return rc;
    }

    for (i = 0; i < count; ++i) {
        ptr[i] = value;
    }

    return MO_OK;
}

int mo_matrix_copy(const double *src, size_t rows, size_t cols, double **out_ptr) {
    size_t i;
    size_t count;
    int rc;

    if (out_ptr == NULL) {
        return MO_ERR_NULL_PTR;
    }

    rc = mo_validate_matrix_ptr(src, rows, cols);
    if (rc != MO_OK) {
        return rc;
    }

    rc = mo_matrix_alloc(rows, cols, out_ptr);
    if (rc != MO_OK) {
        return rc;
    }

    rc = mo_matrix_element_count(rows, cols, &count);
    if (rc != MO_OK) {
        mo_matrix_free(*out_ptr);
        *out_ptr = NULL;
        return rc;
    }

    for (i = 0; i < count; ++i) {
        (*out_ptr)[i] = src[i];
    }

    return MO_OK;
}

int mo_matrix_multiply_dyn(
    const double *a,
    const double *b,
    size_t rows_a,
    size_t cols_a,
    size_t cols_b,
    double **out_ptr
) {
    size_t i;
    size_t j;
    size_t k;
    int rc;

    if (a == NULL || b == NULL || out_ptr == NULL) {
        return MO_ERR_NULL_PTR;
    }
    if (rows_a == 0 || cols_a == 0 || cols_b == 0) {
        return MO_ERR_INVALID_ARG;
    }

    rc = mo_matrix_alloc(rows_a, cols_b, out_ptr);
    if (rc != MO_OK) {
        return rc;
    }

    for (i = 0; i < rows_a; ++i) {
        for (j = 0; j < cols_b; ++j) {
            double sum = 0.0;
            for (k = 0; k < cols_a; ++k) {
                sum += a[i * cols_a + k] * b[k * cols_b + j];
            }
            (*out_ptr)[i * cols_b + j] = sum;
        }
    }

    return MO_OK;
}

#include "math_ops.h"
#include "mo_common.h"

int mo_validate_not_null(const void *ptr) {
    return ptr == NULL ? MO_ERR_NULL_PTR : MO_OK;
}

int mo_matrix_element_count(size_t rows, size_t cols, size_t *out_count) {
    if (out_count == NULL) {
        return MO_ERR_NULL_PTR;
    }
    if (rows == 0 || cols == 0) {
        return MO_ERR_INVALID_ARG;
    }
    if (rows > ((size_t)-1) / cols) {
        return MO_ERR_OVERFLOW;
    }

    *out_count = rows * cols;
    return MO_OK;
}

int mo_validate_matrix_ptr(const double *ptr, size_t rows, size_t cols) {
    size_t unused_count;
    int rc = mo_validate_not_null(ptr);
    if (rc != MO_OK) {
        return rc;
    }

    return mo_matrix_element_count(rows, cols, &unused_count);
}

int mo_is_near_zero(double value) {
    const double epsilon = 1e-12;
    return value > -epsilon && value < epsilon;
}

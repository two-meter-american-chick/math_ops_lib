#ifndef MO_COMMON_H
#define MO_COMMON_H

#include <stddef.h>

int mo_validate_not_null(const void *ptr);
int mo_matrix_element_count(size_t rows, size_t cols, size_t *out_count);
int mo_validate_matrix_ptr(const double *ptr, size_t rows, size_t cols);
int mo_is_near_zero(double value);

#endif

#ifndef MATH_OPS_H
#define MATH_OPS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) && defined(MO_BUILD_DLL)
#define MO_API __declspec(dllexport)
#elif defined(_WIN32) && defined(MO_USE_DLL)
#define MO_API __declspec(dllimport)
#else
#define MO_API
#endif

#define MO_OK 0
#define MO_ERR_NULL_PTR -1
#define MO_ERR_INVALID_ARG -2
#define MO_ERR_OVERFLOW -3
#define MO_ERR_ALLOC -4

MO_API double mo_add(double a, double b);
MO_API double mo_subtract(double a, double b);
MO_API double mo_multiply(double a, double b);
MO_API int mo_divide(double a, double b, double *result);
MO_API double mo_power(double base, int exponent);
MO_API double mo_abs(double value);
MO_API int mo_sqrt(double value, double *result);
MO_API int mo_factorial(unsigned int n, unsigned long long *result);
MO_API int mo_gcd(int a, int b, int *result);
MO_API int mo_lcm(int a, int b, long long *result);

/* Matrices use row-major layout. */
MO_API int mo_matrix_multiply_2x2(const double *a, const double *b, double *result);
MO_API int mo_matrix_multiply_3x3(const double *a, const double *b, double *result);
MO_API int mo_matrix_determinant_3x3(const double *m, double *result);
MO_API int mo_matrix_inverse_2x2(const double *m, double *result);
MO_API int mo_solve_linear_2x2(const double *a, const double *b, double *x);

/* Dynamic memory matrix API (row-major). */
MO_API int mo_matrix_alloc(size_t rows, size_t cols, double **out_ptr);
MO_API int mo_matrix_free(double *ptr);
MO_API int mo_matrix_fill(double *ptr, size_t rows, size_t cols, double value);
MO_API int mo_matrix_copy(const double *src, size_t rows, size_t cols, double **out_ptr);
MO_API int mo_matrix_multiply_dyn(
    const double *a,
    const double *b,
    size_t rows_a,
    size_t cols_a,
    size_t cols_b,
    double **out_ptr
);

#ifdef __cplusplus
}
#endif

#endif

#include "math_ops.h"

#include <stdio.h>

static void print_matrix_2x2(const double *m) {
    printf("[[%.3f, %.3f], [%.3f, %.3f]]\n", m[0], m[1], m[2], m[3]);
}

static void print_matrix_3x3(const double *m) {
    printf("[[%.3f, %.3f, %.3f], [%.3f, %.3f, %.3f], [%.3f, %.3f, %.3f]]\n",
           m[0], m[1], m[2],
           m[3], m[4], m[5],
           m[6], m[7], m[8]);
}

static void print_matrix_dyn(const double *m, size_t rows, size_t cols) {
    size_t i;
    size_t j;

    printf("[");
    for (i = 0; i < rows; ++i) {
        printf("[");
        for (j = 0; j < cols; ++j) {
            printf("%.3f", m[i * cols + j]);
            if (j + 1 < cols) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1 < rows) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    double div_result;
    double sqrt_result;
    unsigned long long factorial_result;
    int gcd_result;
    long long lcm_result;

    double a2[4] = {1.0, 2.0, 3.0, 4.0};
    double b2[4] = {2.0, 0.0, 1.0, 2.0};
    double r2[4];

    double a3[9] = {1.0, 2.0, 3.0,
                    0.0, 1.0, 4.0,
                    5.0, 6.0, 0.0};
    double b3[9] = {7.0, 8.0, 9.0,
                    2.0, 3.0, 4.0,
                    1.0, 0.0, 6.0};
    double r3[9];

    double det3;

    double inv_input[4] = {4.0, 7.0, 2.0, 6.0};
    double inv2[4];

    double system_a[4] = {2.0, 1.0, 5.0, 3.0};
    double system_b[2] = {1.0, 2.0};
    double system_x[2];

    double dyn_a_values[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double dyn_b_values[6] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    double *dyn_a = NULL;
    double *dyn_b = NULL;
    double *dyn_c = NULL;
    double *dyn_copy = NULL;
    size_t i;

    printf("mo_add(5, 3) = %.2f\n", mo_add(5.0, 3.0));
    printf("mo_subtract(5, 3) = %.2f\n", mo_subtract(5.0, 3.0));
    printf("mo_multiply(5, 3) = %.2f\n", mo_multiply(5.0, 3.0));

    if (mo_divide(10.0, 2.0, &div_result) == MO_OK) {
        printf("mo_divide(10, 2) = %.2f\n", div_result);
    }

    printf("mo_power(2, 8) = %.2f\n", mo_power(2.0, 8));
    printf("mo_abs(-12.5) = %.2f\n", mo_abs(-12.5));

    if (mo_sqrt(81.0, &sqrt_result) == MO_OK) {
        printf("mo_sqrt(81) = %.2f\n", sqrt_result);
    }

    if (mo_factorial(10, &factorial_result) == MO_OK) {
        printf("mo_factorial(10) = %llu\n", factorial_result);
    }

    if (mo_gcd(84, 30, &gcd_result) == MO_OK) {
        printf("mo_gcd(84, 30) = %d\n", gcd_result);
    }

    if (mo_lcm(21, 6, &lcm_result) == MO_OK) {
        printf("mo_lcm(21, 6) = %lld\n", lcm_result);
    }

    if (mo_matrix_multiply_2x2(a2, b2, r2) == MO_OK) {
        printf("mo_matrix_multiply_2x2 = ");
        print_matrix_2x2(r2);
    }

    if (mo_matrix_multiply_3x3(a3, b3, r3) == MO_OK) {
        printf("mo_matrix_multiply_3x3 = ");
        print_matrix_3x3(r3);
    }

    if (mo_matrix_determinant_3x3(a3, &det3) == MO_OK) {
        printf("mo_matrix_determinant_3x3 = %.2f\n", det3);
    }

    if (mo_matrix_inverse_2x2(inv_input, inv2) == MO_OK) {
        printf("mo_matrix_inverse_2x2 = ");
        print_matrix_2x2(inv2);
    }

    if (mo_solve_linear_2x2(system_a, system_b, system_x) == MO_OK) {
        printf("mo_solve_linear_2x2 -> x = %.2f, y = %.2f\n", system_x[0], system_x[1]);
    }

    if (mo_matrix_alloc(2, 3, &dyn_a) == MO_OK && mo_matrix_alloc(3, 2, &dyn_b) == MO_OK) {
        for (i = 0; i < 6; ++i) {
            dyn_a[i] = dyn_a_values[i];
            dyn_b[i] = dyn_b_values[i];
        }

        if (mo_matrix_multiply_dyn(dyn_a, dyn_b, 2, 3, 2, &dyn_c) == MO_OK) {
            printf("mo_matrix_multiply_dyn(2x3 * 3x2) = ");
            print_matrix_dyn(dyn_c, 2, 2);
        }

        if (mo_matrix_copy(dyn_a, 2, 3, &dyn_copy) == MO_OK) {
            mo_matrix_fill(dyn_copy, 2, 3, 1.5);
            printf("mo_matrix_fill on copied matrix = ");
            print_matrix_dyn(dyn_copy, 2, 3);
        }
    }

    mo_matrix_free(dyn_a);
    mo_matrix_free(dyn_b);
    mo_matrix_free(dyn_c);
    mo_matrix_free(dyn_copy);

    return 0;
}

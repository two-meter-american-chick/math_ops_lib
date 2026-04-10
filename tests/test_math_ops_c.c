#include "math_ops.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>

static int g_tests_run = 0;
static int g_tests_failed = 0;

static int approx(double a, double b, double eps) {
    return fabs(a - b) <= eps;
}

#define EXPECT_TRUE(cond, msg) do { \
    ++g_tests_run; \
    if (!(cond)) { \
        ++g_tests_failed; \
        printf("FAIL: %s\\n", msg); \
    } \
} while (0)

#define EXPECT_INT_EQ(expected, actual, msg) EXPECT_TRUE((expected) == (actual), msg)

static void test_scalar(void) {
    double div_result;
    double sqrt_result;
    unsigned long long fact_result;
    int gcd_result;
    long long lcm_result;

    EXPECT_TRUE(approx(mo_add(5.0, 3.0), 8.0, 1e-12), "mo_add");
    EXPECT_TRUE(approx(mo_subtract(5.0, 3.0), 2.0, 1e-12), "mo_subtract");
    EXPECT_TRUE(approx(mo_multiply(5.0, 3.0), 15.0, 1e-12), "mo_multiply");

    EXPECT_INT_EQ(MO_OK, mo_divide(10.0, 2.0, &div_result), "mo_divide status");
    EXPECT_TRUE(approx(div_result, 5.0, 1e-12), "mo_divide value");
    EXPECT_INT_EQ(MO_ERR_INVALID_ARG, mo_divide(10.0, 0.0, &div_result), "mo_divide by zero");
    EXPECT_INT_EQ(MO_ERR_NULL_PTR, mo_divide(10.0, 2.0, NULL), "mo_divide null output");

    EXPECT_TRUE(approx(mo_power(2.0, 10), 1024.0, 1e-12), "mo_power");
    EXPECT_TRUE(approx(mo_abs(-123.456), 123.456, 1e-12), "mo_abs");

    EXPECT_INT_EQ(MO_OK, mo_sqrt(81.0, &sqrt_result), "mo_sqrt status");
    EXPECT_TRUE(approx(sqrt_result, 9.0, 1e-9), "mo_sqrt value");
    EXPECT_INT_EQ(MO_ERR_INVALID_ARG, mo_sqrt(-1.0, &sqrt_result), "mo_sqrt negative");

    EXPECT_INT_EQ(MO_OK, mo_factorial(10, &fact_result), "mo_factorial status");
    EXPECT_TRUE(fact_result == 3628800ULL, "mo_factorial value");

    EXPECT_INT_EQ(MO_OK, mo_gcd(84, 30, &gcd_result), "mo_gcd status");
    EXPECT_TRUE(gcd_result == 6, "mo_gcd value");

    EXPECT_INT_EQ(MO_OK, mo_lcm(21, 6, &lcm_result), "mo_lcm status");
    EXPECT_TRUE(lcm_result == 42LL, "mo_lcm value");
}

static void test_matrix_fixed(void) {
    double a2[4] = {1.0, 2.0, 3.0, 4.0};
    double b2[4] = {2.0, 0.0, 1.0, 2.0};
    double r2[4] = {0};

    double a3[9] = {1.0, 2.0, 3.0,
                    0.0, 1.0, 4.0,
                    5.0, 6.0, 0.0};
    double b3[9] = {7.0, 8.0, 9.0,
                    2.0, 3.0, 4.0,
                    1.0, 0.0, 6.0};
    double r3[9] = {0};
    double det3 = 0.0;
    double inv2[4] = {0};

    double system_a[4] = {2.0, 1.0, 5.0, 3.0};
    double system_b[2] = {1.0, 2.0};
    double system_x[2] = {0};

    EXPECT_INT_EQ(MO_OK, mo_matrix_multiply_2x2(a2, b2, r2), "mo_matrix_multiply_2x2 status");
    EXPECT_TRUE(approx(r2[0], 4.0, 1e-12) && approx(r2[1], 4.0, 1e-12) &&
                approx(r2[2], 10.0, 1e-12) && approx(r2[3], 8.0, 1e-12), "mo_matrix_multiply_2x2 value");

    EXPECT_INT_EQ(MO_OK, mo_matrix_multiply_3x3(a3, b3, r3), "mo_matrix_multiply_3x3 status");
    EXPECT_TRUE(approx(r3[0], 14.0, 1e-12) && approx(r3[8], 69.0, 1e-12), "mo_matrix_multiply_3x3 value");

    EXPECT_INT_EQ(MO_OK, mo_matrix_determinant_3x3(a3, &det3), "mo_matrix_determinant_3x3 status");
    EXPECT_TRUE(approx(det3, 1.0, 1e-12), "mo_matrix_determinant_3x3 value");

    EXPECT_INT_EQ(MO_OK, mo_matrix_inverse_2x2((double[]){4.0, 7.0, 2.0, 6.0}, inv2), "mo_matrix_inverse_2x2 status");
    EXPECT_TRUE(approx(inv2[0], 0.6, 1e-12) && approx(inv2[1], -0.7, 1e-12) &&
                approx(inv2[2], -0.2, 1e-12) && approx(inv2[3], 0.4, 1e-12), "mo_matrix_inverse_2x2 value");

    EXPECT_INT_EQ(MO_ERR_INVALID_ARG, mo_matrix_inverse_2x2((double[]){1.0, 2.0, 2.0, 4.0}, inv2), "mo_matrix_inverse_2x2 singular");

    EXPECT_INT_EQ(MO_OK, mo_solve_linear_2x2(system_a, system_b, system_x), "mo_solve_linear_2x2 status");
    EXPECT_TRUE(approx(system_x[0], 1.0, 1e-12) && approx(system_x[1], -1.0, 1e-12), "mo_solve_linear_2x2 value");

    EXPECT_INT_EQ(MO_ERR_NULL_PTR, mo_matrix_multiply_2x2(NULL, b2, r2), "mo_matrix_multiply_2x2 null input");
}

static void test_matrix_dynamic(void) {
    double src[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double rhs[6] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    double *m = NULL;
    double *copy = NULL;
    double *product = NULL;
    double *huge = NULL;
    double *tmp = NULL;
    size_t huge_cols = ((size_t)-1) / sizeof(double);

    EXPECT_INT_EQ(MO_OK, mo_matrix_alloc(2, 3, &m), "mo_matrix_alloc status");
    EXPECT_TRUE(m != NULL, "mo_matrix_alloc pointer");

    EXPECT_INT_EQ(MO_OK, mo_matrix_fill(m, 2, 3, 2.5), "mo_matrix_fill status");
    EXPECT_TRUE(approx(m[0], 2.5, 1e-12) && approx(m[5], 2.5, 1e-12), "mo_matrix_fill value");

    EXPECT_INT_EQ(MO_OK, mo_matrix_copy(src, 2, 3, &copy), "mo_matrix_copy status");
    EXPECT_TRUE(copy != NULL && approx(copy[0], 1.0, 1e-12) && approx(copy[5], 6.0, 1e-12), "mo_matrix_copy value");

    EXPECT_INT_EQ(MO_OK, mo_matrix_multiply_dyn(src, rhs, 2, 3, 2, &product), "mo_matrix_multiply_dyn status");
    EXPECT_TRUE(product != NULL, "mo_matrix_multiply_dyn pointer");
    EXPECT_TRUE(approx(product[0], 58.0, 1e-12) && approx(product[1], 64.0, 1e-12) &&
                approx(product[2], 139.0, 1e-12) && approx(product[3], 154.0, 1e-12), "mo_matrix_multiply_dyn value");

    EXPECT_INT_EQ(MO_ERR_NULL_PTR, mo_matrix_alloc(2, 2, NULL), "mo_matrix_alloc null out ptr");
    EXPECT_INT_EQ(MO_ERR_INVALID_ARG, mo_matrix_alloc(0, 2, &tmp), "mo_matrix_alloc zero rows");
    EXPECT_INT_EQ(MO_ERR_OVERFLOW, mo_matrix_alloc((size_t)-1, 2, &tmp), "mo_matrix_alloc overflow");
    EXPECT_INT_EQ(MO_ERR_NULL_PTR, mo_matrix_fill(NULL, 2, 2, 1.0), "mo_matrix_fill null matrix");
    EXPECT_INT_EQ(MO_ERR_INVALID_ARG, mo_matrix_fill(m, 0, 2, 1.0), "mo_matrix_fill invalid dims");
    EXPECT_INT_EQ(MO_ERR_NULL_PTR, mo_matrix_copy(NULL, 2, 2, &copy), "mo_matrix_copy null source");
    EXPECT_INT_EQ(MO_ERR_INVALID_ARG, mo_matrix_multiply_dyn(src, rhs, 0, 3, 2, &product), "mo_matrix_multiply_dyn invalid dims");
    EXPECT_INT_EQ(MO_ERR_ALLOC, mo_matrix_alloc(1, huge_cols, &huge), "mo_matrix_alloc allocation failure path");

    EXPECT_INT_EQ(MO_OK, mo_matrix_free(m), "mo_matrix_free m");
    EXPECT_INT_EQ(MO_OK, mo_matrix_free(copy), "mo_matrix_free copy");
    EXPECT_INT_EQ(MO_OK, mo_matrix_free(product), "mo_matrix_free product");
    EXPECT_INT_EQ(MO_OK, mo_matrix_free(huge), "mo_matrix_free huge");
    EXPECT_INT_EQ(MO_OK, mo_matrix_free(tmp), "mo_matrix_free tmp");
}

int main(void) {
    test_scalar();
    test_matrix_fixed();
    test_matrix_dynamic();

    printf("C tests run: %d\n", g_tests_run);

    if (g_tests_failed != 0) {
        printf("C tests failed: %d\n", g_tests_failed);
        return 1;
    }

    printf("C tests passed.\n");
    return 0;
}

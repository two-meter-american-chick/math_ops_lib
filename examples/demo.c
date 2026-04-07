#include "math_ops.h"

#include <stdio.h>

int main(void) {
    double div_result;
    double sqrt_result;
    unsigned long long factorial_result;
    int gcd_result;
    long long lcm_result;

    printf("mo_add(5, 3) = %.2f\n", mo_add(5.0, 3.0));
    printf("mo_subtract(5, 3) = %.2f\n", mo_subtract(5.0, 3.0));
    printf("mo_multiply(5, 3) = %.2f\n", mo_multiply(5.0, 3.0));

    if (mo_divide(10.0, 2.0, &div_result) == 0) {
        printf("mo_divide(10, 2) = %.2f\n", div_result);
    }

    printf("mo_power(2, 8) = %.2f\n", mo_power(2.0, 8));
    printf("mo_abs(-12.5) = %.2f\n", mo_abs(-12.5));

    if (mo_sqrt(81.0, &sqrt_result) == 0) {
        printf("mo_sqrt(81) = %.2f\n", sqrt_result);
    }

    if (mo_factorial(10, &factorial_result) == 0) {
        printf("mo_factorial(10) = %llu\n", factorial_result);
    }

    if (mo_gcd(84, 30, &gcd_result) == 0) {
        printf("mo_gcd(84, 30) = %d\n", gcd_result);
    }

    if (mo_lcm(21, 6, &lcm_result) == 0) {
        printf("mo_lcm(21, 6) = %lld\n", lcm_result);
    }

    return 0;
}

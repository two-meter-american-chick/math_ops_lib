#include "math_ops.h"
#include "mo_common.h"

#include <limits.h>

static long long iabs_ll(int value) {
    return value < 0 ? -(long long)value : (long long)value;
}

double mo_add(double a, double b) {
    return a + b;
}

double mo_subtract(double a, double b) {
    return a - b;
}

double mo_multiply(double a, double b) {
    return a * b;
}

int mo_divide(double a, double b, double *result) {
    if (result == NULL) {
        return MO_ERR_NULL_PTR;
    }
    if (mo_is_near_zero(b)) {
        return MO_ERR_INVALID_ARG;
    }

    *result = a / b;
    return MO_OK;
}

double mo_power(double base, int exponent) {
    double result = 1.0;
    long long exp = exponent;

    if (exp < 0) {
        exp = -exp;
    }

    while (exp > 0) {
        if ((exp & 1LL) == 1LL) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }

    if (exponent < 0) {
        if (mo_is_near_zero(result)) {
            return 0.0;
        }
        return 1.0 / result;
    }

    return result;
}

double mo_abs(double value) {
    return value < 0.0 ? -value : value;
}

int mo_sqrt(double value, double *result) {
    double estimate;
    int i;

    if (result == NULL) {
        return MO_ERR_NULL_PTR;
    }
    if (value < 0.0) {
        return MO_ERR_INVALID_ARG;
    }
    if (value == 0.0) {
        *result = 0.0;
        return MO_OK;
    }

    estimate = value < 1.0 ? 1.0 : value;

    for (i = 0; i < 50; ++i) {
        estimate = 0.5 * (estimate + value / estimate);
    }

    *result = estimate;
    return MO_OK;
}

int mo_factorial(unsigned int n, unsigned long long *result) {
    unsigned long long acc = 1;
    unsigned int i;

    if (result == NULL) {
        return MO_ERR_NULL_PTR;
    }

    for (i = 2; i <= n; ++i) {
        if (acc > ULLONG_MAX / i) {
            return MO_ERR_OVERFLOW;
        }
        acc *= i;
    }

    *result = acc;
    return MO_OK;
}

int mo_gcd(int a, int b, int *result) {
    long long x;
    long long y;

    if (result == NULL) {
        return MO_ERR_NULL_PTR;
    }

    x = iabs_ll(a);
    y = iabs_ll(b);

    while (y != 0) {
        long long temp = x % y;
        x = y;
        y = temp;
    }

    if (x > INT_MAX) {
        return MO_ERR_OVERFLOW;
    }

    *result = (int)x;
    return MO_OK;
}

int mo_lcm(int a, int b, long long *result) {
    int gcd_value;
    long long x;
    long long y;
    long long partial;

    if (result == NULL) {
        return MO_ERR_NULL_PTR;
    }

    if (a == 0 || b == 0) {
        *result = 0;
        return MO_OK;
    }

    if (mo_gcd(a, b, &gcd_value) != MO_OK || gcd_value == 0) {
        return MO_ERR_INVALID_ARG;
    }

    x = iabs_ll(a);
    y = iabs_ll(b);
    partial = x / gcd_value;

    if (partial > LLONG_MAX / y) {
        return MO_ERR_OVERFLOW;
    }

    *result = partial * y;
    return MO_OK;
}

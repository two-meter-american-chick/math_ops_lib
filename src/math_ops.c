#include "math_ops.h"

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
    if (result == 0) {
        return -1;
    }
    if (b == 0.0) {
        return -2;
    }

    *result = a / b;
    return 0;
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
        if (result == 0.0) {
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

    if (result == 0) {
        return -1;
    }
    if (value < 0.0) {
        return -2;
    }
    if (value == 0.0) {
        *result = 0.0;
        return 0;
    }

    estimate = value < 1.0 ? 1.0 : value;

    for (i = 0; i < 50; ++i) {
        estimate = 0.5 * (estimate + value / estimate);
    }

    *result = estimate;
    return 0;
}

int mo_factorial(unsigned int n, unsigned long long *result) {
    unsigned long long acc = 1;
    unsigned int i;

    if (result == 0) {
        return -1;
    }

    for (i = 2; i <= n; ++i) {
        if (acc > ULLONG_MAX / i) {
            return -2;
        }
        acc *= i;
    }

    *result = acc;
    return 0;
}

int mo_gcd(int a, int b, int *result) {
    long long x;
    long long y;

    if (result == 0) {
        return -1;
    }

    x = iabs_ll(a);
    y = iabs_ll(b);

    while (y != 0) {
        long long temp = x % y;
        x = y;
        y = temp;
    }

    if (x > INT_MAX) {
        return -2;
    }

    *result = (int)x;
    return 0;
}

int mo_lcm(int a, int b, long long *result) {
    int gcd_value;
    long long x;
    long long y;
    long long partial;

    if (result == 0) {
        return -1;
    }

    if (a == 0 || b == 0) {
        *result = 0;
        return 0;
    }

    if (mo_gcd(a, b, &gcd_value) != 0 || gcd_value == 0) {
        return -2;
    }

    x = iabs_ll(a);
    y = iabs_ll(b);
    partial = x / gcd_value;

    if (partial > LLONG_MAX / y) {
        return -2;
    }

    *result = partial * y;
    return 0;
}

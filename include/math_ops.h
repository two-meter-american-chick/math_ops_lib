#ifndef MATH_OPS_H
#define MATH_OPS_H

#ifdef __cplusplus
extern "C" {
#endif

double mo_add(double a, double b);
double mo_subtract(double a, double b);
double mo_multiply(double a, double b);
int mo_divide(double a, double b, double *result);
double mo_power(double base, int exponent);
double mo_abs(double value);
int mo_sqrt(double value, double *result);
int mo_factorial(unsigned int n, unsigned long long *result);
int mo_gcd(int a, int b, int *result);
int mo_lcm(int a, int b, long long *result);

#ifdef __cplusplus
}
#endif

#endif

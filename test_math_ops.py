from __future__ import annotations

import ctypes
from pathlib import Path

MO_OK = 0
MO_ERR_NULL_PTR = -1
MO_ERR_INVALID_ARG = -2
MO_ERR_OVERFLOW = -3
MO_ERR_ALLOC = -4


def find_lib() -> Path:
    candidates = [
        Path.cwd() / "math_ops.dll",
        Path.cwd() / "build" / "math_ops.dll",
        Path.cwd() / "build" / "Debug" / "math_ops.dll",
        Path.cwd() / "build" / "Release" / "math_ops.dll",
    ]
    for path in candidates:
        if path.exists():
            return path
    raise FileNotFoundError(
        "math_ops.dll not found. Build the C library first or place DLL in project root."
    )


def approx(a: float, b: float, eps: float = 1e-9) -> bool:
    return abs(a - b) <= eps


def configure(lib: ctypes.CDLL) -> None:
    c_double = ctypes.c_double
    c_int = ctypes.c_int
    c_uint = ctypes.c_uint
    c_ull = ctypes.c_ulonglong
    c_ll = ctypes.c_longlong
    c_size_t = ctypes.c_size_t

    c_double_p = ctypes.POINTER(c_double)
    c_double_pp = ctypes.POINTER(c_double_p)

    lib.mo_add.argtypes = [c_double, c_double]
    lib.mo_add.restype = c_double

    lib.mo_subtract.argtypes = [c_double, c_double]
    lib.mo_subtract.restype = c_double

    lib.mo_multiply.argtypes = [c_double, c_double]
    lib.mo_multiply.restype = c_double

    lib.mo_divide.argtypes = [c_double, c_double, c_double_p]
    lib.mo_divide.restype = c_int

    lib.mo_power.argtypes = [c_double, c_int]
    lib.mo_power.restype = c_double

    lib.mo_abs.argtypes = [c_double]
    lib.mo_abs.restype = c_double

    lib.mo_sqrt.argtypes = [c_double, c_double_p]
    lib.mo_sqrt.restype = c_int

    lib.mo_factorial.argtypes = [c_uint, ctypes.POINTER(c_ull)]
    lib.mo_factorial.restype = c_int

    lib.mo_gcd.argtypes = [c_int, c_int, ctypes.POINTER(c_int)]
    lib.mo_gcd.restype = c_int

    lib.mo_lcm.argtypes = [c_int, c_int, ctypes.POINTER(c_ll)]
    lib.mo_lcm.restype = c_int

    lib.mo_matrix_multiply_2x2.argtypes = [c_double_p, c_double_p, c_double_p]
    lib.mo_matrix_multiply_2x2.restype = c_int

    lib.mo_matrix_multiply_3x3.argtypes = [c_double_p, c_double_p, c_double_p]
    lib.mo_matrix_multiply_3x3.restype = c_int

    lib.mo_matrix_determinant_3x3.argtypes = [c_double_p, c_double_p]
    lib.mo_matrix_determinant_3x3.restype = c_int

    lib.mo_matrix_inverse_2x2.argtypes = [c_double_p, c_double_p]
    lib.mo_matrix_inverse_2x2.restype = c_int

    lib.mo_solve_linear_2x2.argtypes = [c_double_p, c_double_p, c_double_p]
    lib.mo_solve_linear_2x2.restype = c_int

    lib.mo_matrix_alloc.argtypes = [c_size_t, c_size_t, c_double_pp]
    lib.mo_matrix_alloc.restype = c_int

    lib.mo_matrix_free.argtypes = [c_double_p]
    lib.mo_matrix_free.restype = c_int

    lib.mo_matrix_fill.argtypes = [c_double_p, c_size_t, c_size_t, c_double]
    lib.mo_matrix_fill.restype = c_int

    lib.mo_matrix_copy.argtypes = [c_double_p, c_size_t, c_size_t, c_double_pp]
    lib.mo_matrix_copy.restype = c_int

    lib.mo_matrix_multiply_dyn.argtypes = [c_double_p, c_double_p, c_size_t, c_size_t, c_size_t, c_double_pp]
    lib.mo_matrix_multiply_dyn.restype = c_int


def main() -> None:
    lib_path = find_lib()
    lib = ctypes.CDLL(str(lib_path))
    configure(lib)

    assert approx(lib.mo_add(10.5, 2.5), 13.0)
    assert approx(lib.mo_subtract(10.5, 2.5), 8.0)
    assert approx(lib.mo_multiply(6.0, 7.0), 42.0)

    div_result = ctypes.c_double()
    assert lib.mo_divide(22.0, 7.0, ctypes.byref(div_result)) == MO_OK
    assert approx(div_result.value, 22.0 / 7.0)
    assert lib.mo_divide(10.0, 0.0, ctypes.byref(div_result)) == MO_ERR_INVALID_ARG

    assert approx(lib.mo_power(2.0, 10), 1024.0)
    assert approx(lib.mo_abs(-123.456), 123.456)

    sqrt_result = ctypes.c_double()
    assert lib.mo_sqrt(144.0, ctypes.byref(sqrt_result)) == MO_OK
    assert approx(sqrt_result.value, 12.0)

    factorial_result = ctypes.c_ulonglong()
    assert lib.mo_factorial(10, ctypes.byref(factorial_result)) == MO_OK
    assert factorial_result.value == 3628800

    gcd_result = ctypes.c_int()
    assert lib.mo_gcd(84, 30, ctypes.byref(gcd_result)) == MO_OK
    assert gcd_result.value == 6

    lcm_result = ctypes.c_longlong()
    assert lib.mo_lcm(21, 6, ctypes.byref(lcm_result)) == MO_OK
    assert lcm_result.value == 42

    a2 = (ctypes.c_double * 4)(1.0, 2.0, 3.0, 4.0)
    b2 = (ctypes.c_double * 4)(2.0, 0.0, 1.0, 2.0)
    r2 = (ctypes.c_double * 4)()
    assert lib.mo_matrix_multiply_2x2(a2, b2, r2) == MO_OK
    assert [r2[i] for i in range(4)] == [4.0, 4.0, 10.0, 8.0]

    a3 = (ctypes.c_double * 9)(1.0, 2.0, 3.0, 0.0, 1.0, 4.0, 5.0, 6.0, 0.0)
    b3 = (ctypes.c_double * 9)(7.0, 8.0, 9.0, 2.0, 3.0, 4.0, 1.0, 0.0, 6.0)
    r3 = (ctypes.c_double * 9)()
    assert lib.mo_matrix_multiply_3x3(a3, b3, r3) == MO_OK
    assert [r3[i] for i in range(9)] == [14.0, 14.0, 35.0, 6.0, 3.0, 28.0, 47.0, 58.0, 69.0]

    det3 = ctypes.c_double()
    assert lib.mo_matrix_determinant_3x3(a3, ctypes.byref(det3)) == MO_OK
    assert approx(det3.value, 1.0)

    inv_in = (ctypes.c_double * 4)(4.0, 7.0, 2.0, 6.0)
    inv_out = (ctypes.c_double * 4)()
    assert lib.mo_matrix_inverse_2x2(inv_in, inv_out) == MO_OK
    expected_inv = [0.6, -0.7, -0.2, 0.4]
    for i in range(4):
        assert approx(inv_out[i], expected_inv[i], eps=1e-12)

    system_a = (ctypes.c_double * 4)(2.0, 1.0, 5.0, 3.0)
    system_b = (ctypes.c_double * 2)(1.0, 2.0)
    system_x = (ctypes.c_double * 2)()
    assert lib.mo_solve_linear_2x2(system_a, system_b, system_x) == MO_OK
    assert approx(system_x[0], 1.0)
    assert approx(system_x[1], -1.0)

    dyn_ptr = ctypes.POINTER(ctypes.c_double)()
    assert lib.mo_matrix_alloc(2, 3, ctypes.byref(dyn_ptr)) == MO_OK
    assert bool(dyn_ptr)

    assert lib.mo_matrix_fill(dyn_ptr, 2, 3, 2.5) == MO_OK
    assert approx(dyn_ptr[0], 2.5)
    assert approx(dyn_ptr[5], 2.5)

    src = (ctypes.c_double * 6)(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
    copy_ptr = ctypes.POINTER(ctypes.c_double)()
    assert lib.mo_matrix_copy(src, 2, 3, ctypes.byref(copy_ptr)) == MO_OK
    assert bool(copy_ptr)
    assert [copy_ptr[i] for i in range(6)] == [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]

    rhs = (ctypes.c_double * 6)(7.0, 8.0, 9.0, 10.0, 11.0, 12.0)
    product_ptr = ctypes.POINTER(ctypes.c_double)()
    assert lib.mo_matrix_multiply_dyn(src, rhs, 2, 3, 2, ctypes.byref(product_ptr)) == MO_OK
    assert bool(product_ptr)
    assert [product_ptr[i] for i in range(4)] == [58.0, 64.0, 139.0, 154.0]

    tmp_ptr = ctypes.POINTER(ctypes.c_double)()
    assert lib.mo_matrix_alloc(0, 3, ctypes.byref(tmp_ptr)) == MO_ERR_INVALID_ARG
    assert lib.mo_matrix_alloc(ctypes.c_size_t(-1).value, 2, ctypes.byref(tmp_ptr)) == MO_ERR_OVERFLOW
    assert lib.mo_matrix_fill(None, 2, 2, 1.0) == MO_ERR_NULL_PTR
    assert lib.mo_matrix_copy(None, 2, 2, ctypes.byref(copy_ptr)) == MO_ERR_NULL_PTR

    assert lib.mo_matrix_free(dyn_ptr) == MO_OK
    assert lib.mo_matrix_free(copy_ptr) == MO_OK
    assert lib.mo_matrix_free(product_ptr) == MO_OK
    assert lib.mo_matrix_free(tmp_ptr) == MO_OK

    print(f"OK: scalar, matrix and dynamic-memory C functions passed via ctypes. DLL: {lib_path}")


if __name__ == "__main__":
    main()

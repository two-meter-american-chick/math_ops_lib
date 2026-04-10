# Math Ops C Library

Math library in C for linear algebra and calculus-related operations.

## Project structure

- `include/math_ops.h` - single public API facade.
- `src/mo_scalar.c` - scalar operations.
- `src/mo_matrix.c` - fixed-size matrix operations.
- `src/mo_memory.c` - dynamic memory matrix operations.
- `src/mo_common.c` + `src/mo_common.h` - shared validation/error layer.

## Error codes

- `MO_OK` (0) - success.
- `MO_ERR_NULL_PTR` (-1) - null pointer.
- `MO_ERR_INVALID_ARG` (-2) - invalid argument/domain.
- `MO_ERR_OVERFLOW` (-3) - arithmetic/size overflow.
- `MO_ERR_ALLOC` (-4) - allocation failure.

## API overview

### Scalar functions (10)

`mo_add`, `mo_subtract`, `mo_multiply`, `mo_divide`, `mo_power`, `mo_abs`, `mo_sqrt`, `mo_factorial`, `mo_gcd`, `mo_lcm`

### Matrix fixed-size functions (5)

`mo_matrix_multiply_2x2`, `mo_matrix_multiply_3x3`, `mo_matrix_determinant_3x3`, `mo_matrix_inverse_2x2`, `mo_solve_linear_2x2`

### Dynamic memory functions (5)

`mo_matrix_alloc`, `mo_matrix_free`, `mo_matrix_fill`, `mo_matrix_copy`, `mo_matrix_multiply_dyn`

All matrices use row-major layout.

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
```

## Build DLL on Windows (MSVC Build Tools)

```cmd
"C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat" && cl /nologo /LD /DMO_BUILD_DLL /I include src\mo_common.c src\mo_scalar.c src\mo_matrix.c src\mo_memory.c /link /OUT:math_ops.dll
```

## Run demo

```powershell
.\build\Debug\math_ops_demo.exe
```

## Tests

### C unit tests

```powershell
.\build\Debug\math_ops_c_tests.exe
```

### Python integration tests (ctypes)

```powershell
C:\Users\Вадим\AppData\Local\Programs\Python\Python312\python.exe test_math_ops.py
```

### Strict Jupyter notebook (native DLL only)

`math_ops_examples.ipynb`

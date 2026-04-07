# Math Ops C Library

Небольшая C-библиотека с 10 математическими функциями.

## Функции

1. `mo_add` - сложение
2. `mo_subtract` - вычитание
3. `mo_multiply` - умножение
4. `mo_divide` - деление с проверкой деления на ноль
5. `mo_power` - возведение в целую степень
6. `mo_abs` - модуль числа
7. `mo_sqrt` - квадратный корень (метод Ньютона)
8. `mo_factorial` - факториал с проверкой переполнения
9. `mo_gcd` - НОД
10. `mo_lcm` - НОК

## Сборка

```bash
cmake -S . -B build
cmake --build build
```

## Пример запуска

```bash
./build/math_ops_demo
```

На Windows:

```powershell
.\build\Debug\math_ops_demo.exe
```

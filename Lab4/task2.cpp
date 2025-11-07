#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "Measure.hpp"

using namespace std;

/*
Задание 2

FindRoot

Ограничение времени: 1 с
Ограничение памяти: 64M

Реализовать функцию find_root(f, a, b, tol) , реализующую поиск на интервале (a,b) корня x0
уравнения f(x) = 0 методом двоичного поиска (бисекции). Точность определения x0 не должна превышать
значение tol . Выполнение равенства f = 0 проверять с точностью eps = 1e-6 . Гарантируется наличие
единственного корня на рассматриваемом интервале. Функция f непрерывна и имеет значения разных
знаков на концах интервала (a, b).

Аргументы функции
f — function функция, нуль которой нужно найти
a — левый край интервала поиска корня
b — float правый край интервала поиска корня
tol — float точность локализации корня уравнения f(x) = 0
Возвращаемое значение
Одно число — найденный корень уравнения f(x) = 0.
*/

double find_root(double (*f)(double), float a, float b, float tol)
{
    // Тесты могут быть неккоректными - такие случаи пропускаются
    if (f(a) * f(b) > 0)
        throw runtime_error("f(a) and f(b) must have different signs");

    double c = (a + b) / 2;

    while (f(c) > 1e-6 && (b - a) > tol)
    {
        if (f(a) * f(c) <= 0)
            b = c;
        else
            a = c;

        c = (a + b) / 2;
    }

    return c;
}

int main()
{
    vector<double (*)(double)> funcs = {
        [](double x) { return log(x) - 3; },    [](double x) { return sin(x); },
        [](double x) { return x * x - 2; },     [](double x) { return x * x - 2; },
        [](double x) { return x * x * x - 8; }, [](double x) { return x - exp(-x); },
        [](double x) { return tan(x) - x; },    [](double x) { return (x - 2)*(x - 5); }};

    // Генератор случайных чисел с фиксированным зерном, чтобы результаты были воспроизводимыми
    mt19937 randomGenerator(1917);
    uniform_real_distribution<float> aDist(-30, 0);
    uniform_real_distribution<float> bDist(0, 30);
    uniform_real_distribution<float> tolDist(1e-6, 1e-3);
    uniform_int_distribution<int> fDist(0, funcs.size() - 1);

    int numTests = 1e9;
    for (int i = 0; i < numTests; ++i)
    {
        float a = aDist(randomGenerator);
        float b = bDist(randomGenerator);
        float tol = tolDist(randomGenerator);
        int f_id = fDist(randomGenerator);

        cout << "Функция под № " << f_id << " (" << a << ' ' << b << ' ' << tol << ')' << endl;

        Measure localMes{1, 64};

        try
        {
            auto root = find_root(funcs[f_id], a, b, 1e-6);
            cout << "Test " << i + 1 << ": root ≈ " << root << endl;
        }
        catch (runtime_error)
        {
            cout << "Test " << i + 1 << ": invalid interval" << endl;
        }

        localMes.checkLimit();
    }
}
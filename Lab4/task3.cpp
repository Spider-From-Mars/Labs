#include <iostream>
#include <limits>
#include <random>
#include <unordered_map>

#include "Measure.hpp"

using namespace std;

/*
Ограничение времени: 5 с
Ограничение памяти: 256
Ограничение размера стека: 64M

В прихожей в ряд стоит N тапочек, которые бывают разных размеров, а также левыми и правыми. Гость
выбирает две тапочки, удовлетворяющие следующим условиям: Выбранные тапочки должны быть одного
размера. Из выбранных тапок левая тапка должна стоять левее правой. Если можно выбрать несколько пар
тапочек, удовлетворяющих первым двум условиям, то выбираются две тапочки с наименьшим расстоянием
между ними.

Формат входных данных
В первой строке входных данных записано число тапок N. Во второй строке записаны размеры тапок в
порядке слева направо, при этом левые тапки условно обозначаются отрицательными числами (то есть −s
обозначает левую тапку, а s обозначает правую тапку размера s). Формат выходных данных Выведите одно
число: минимальное расстояние между двумя тапочками одного размера таких, что левая тапочка стоит
левее правой. Если таких пар тапочек нет, то выведите одно число 0
*/

unsigned getDistance(short *arr, unsigned N)
{
    /* Если запоминать последнюю позицию левой тапки каждого размера,
    то когда встречаем правую — мы сразу знаем, где последняя левая, и можем вычислить расстояние.
    */

    unordered_map<short, unsigned> lastLeft; // размер -> индекс последней левой тапки
    auto minDist = numeric_limits<unsigned>::max();

    for (unsigned i = 0; i < N; ++i)
    {
        short val = arr[i];
        if (val < 0)
        {
            lastLeft[-val] = i; // запоминаем, где стояла левая
        }
        else
        {
            // Если в отображении есть такое значение, значит левая тапка уже была
            if (lastLeft.count(val))
            {
                unsigned dist = i - lastLeft[val];
                if (dist < minDist)
                    minDist = dist;
            }
        }
    }

    return minDist;
}

int main()
{
    // Генератор случайных чисел с фиксированным зерном, чтобы результаты были воспроизводимыми
    mt19937 randomGenerator(1917);
    uniform_int_distribution<short> sizeDist(-47, 47);
    uniform_int_distribution<unsigned> nDist(1, 1e9);

    for (size_t test = 0; test < 1e6; test++)
    {
        Measure localMes{1, 64};
        unsigned N = nDist(randomGenerator);

        short *arr = new short[N];
        for (unsigned i = 0; i < N; ++i)
        {
            arr[i] = sizeDist(randomGenerator);
        }

        auto minDist = getDistance(arr, N);
        localMes.checkLimit();

        cout << "Минимальное расстояние = "
             << (minDist == numeric_limits<unsigned>::max() ? 0 : minDist) << endl;
        delete[] arr;
    }
}
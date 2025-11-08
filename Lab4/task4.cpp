#include <algorithm>
#include <iostream>
#include <random>

#include "Measure.hpp"

using namespace std;

/*
Сортировка: сначала чётные

Ограничение времени: 1 с
Ограничение памяти: 64M

Дан список целых чисел. Отсортировать его так, чтобы сначала шли чётные по возрастанию, потом —
нечётные во возрастанию.

Формат входных данных
Одна строка — список чисел через пробел. Длина списка не превосходит 10000.

Формат выходных данных
Отсортированный список чисел через пробел.
*/

int main()
{
    // Можно было бы сделать два массива для четных и нечетных чисел,
    // но тогда использование памяти будет 2 раза больше, так как нельзя заранее определить сколько
    // будет четных и нечетных. Поэтому вместо этого используется один массив и собственная
    // лямбда-функция сортировки
    constexpr unsigned maxSize = 1e4;

    mt19937 randomGenerator(1917);
    uniform_int_distribution<unsigned> sizeDist(0, maxSize);
    uniform_int_distribution<long> nDist(-1e6, 1e6);

    for (unsigned test = 0; test < 1e9; ++test)
    {
        Measure localMes{1, 64};

        // Так как размер входного массива меняется, то следует заново выделять память, чтобы
        // значения предыдущих вычислений не мешали (в случае, если size < size(n-1))
        long *nums = new long[maxSize];
        // Если бы значения вводились из потока ввода,
        // то задача вычислить конкретный размер массива тривиальна
        auto size = sizeDist(randomGenerator);

        for (unsigned i = 0; i < size; ++i)
        {
            nums[i] = nDist(randomGenerator);
        }

        // В роли итератора выступает указатель на массив
        sort(nums, nums + size,
             [](long a, long b)
             {
                 if (a % 2 == 0 && b % 2 != 0)
                     return true;
                 if (a % 2 != 0 && b % 2 == 0)
                     return false;

                 return a < b;
             });

        for (unsigned i = 0; i < size; ++i)
        {
            cout << nums[i] << ' ';
        }
        cout << endl;

        delete[] nums;

        localMes.checkLimit();
    }
}
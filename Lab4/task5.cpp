#include <cstring>
#include <iostream>
#include <random>
#include <stdexcept>

#include "Measure.hpp"

using namespace std;

/*
Поразрядная сортировка

Ограничение времени: 1 с
Ограничение памяти: 64M

Написать программу, осуществляющую поразрядную сортировку введённых целых чисел в двоичной системе
счисления по возрастанию. Внимание! Сначала необходимо считать все введённые числа в один список

Формат входных данных
Последовательность целых чисел, разделённая символом пробел.

Формат выходных данных
Набор расстановок чисел в сортируемом массиве. Внимание! Надо выводить весь массив после КАЖДОЙ
перестановки элементов в нём. Если перестановок не было — ВСЁ РАВНО нужно выводить
*/

namespace Random
{
mt19937 randomGenerator(2006);
uniform_int_distribution<unsigned> lenDist(5, 60);      // длина числа
uniform_int_distribution<unsigned short> bitDist(0, 1); // 0 или 1
uniform_int_distribution<int> countDist(5, 1e5);        // кол-во чисел в тесте
} // namespace Random

void radix(char **nums, unsigned N, unsigned maxSize)
{
    // Массив из двух массивов строк — один bucket для чисел, у которых текущий разряд '0',
    // другой для чисел, у которых текущий разряд '1'
    char **buckets[2];
    buckets[0] = new char *[N];
    buckets[1] = new char *[N];

    unsigned short bucketSizes[2];
    bucketSizes[0] = bucketSizes[1] = 0;

    // Поразрядная сортировка — от младшего к старшему биту
    for (int pos = maxSize - 1; pos >= 0; --pos)
    {
        // "Очистка" корзин
        bucketSizes[0] = bucketSizes[1] = 0;

        // Раскладываем числа по корзинам
        for (unsigned i = 0; i < N; ++i)
        {
            unsigned len = strlen(nums[i]);
            // Так как числа разной длины, то нужно перерасчитать индекс pos (глобальный для всех
            // чисел, от 0 до maxSize - 1) в локальный индекс внутри строки конкретного числа
            int bitIndex = pos - (maxSize - len);

            // Если bitIndex < 0 то это значит, что у числа нет такого разряда, т. е. онo короче, и
            // тогда можно считать, что на этой позиции у него '0'
            char bit = (bitIndex >= 0) ? nums[i][bitIndex] : '0';

            // Здесь снова применяюстя коды символов: '0' - '0' = 0, '1' - '0' = 1
            buckets[bit - '0'][bucketSizes[bit - '0']++] = nums[i];
        }

        // Собираем обратно в nums
        unsigned ni = 0;
        for (unsigned short b = 0; b < 2; ++b)
        {
            for (int j = 0; j < bucketSizes[b]; ++j)
            {
                nums[ni] = buckets[b][j];
                ni++;
            }
        }

        // Вывод после каждой итерации
        for (unsigned i = 0; i < N; ++i)
            cout << nums[i] << ' ';
        cout << endl;
    }

    // Очистка
    delete[] buckets[0];
    delete[] buckets[1];
}

void clear(char **nums, unsigned N)
{
    for (unsigned i = 0; i < N; ++i)
    {
        delete[] nums[i];
    }

    delete[] nums;
}

char **getData(unsigned N)
{
    using Random::randomGenerator;

    // Если бы данные были из потока ввода, тогда следовало бы использовать std::vector,
    // поскольку в нем уже реализованы эффективные методы динамического управления памятью
    unsigned capacity{40};
    // По условиям задачи мы не знаем количество чисел
    char **nums = new char *[capacity];

    // Моделируется ввод из потока
    for (unsigned i = 0; i < N; ++i)
    {
        // Динамическоe выделение памяти
        if (i == capacity)
        {
            capacity *= 2;
            char **tmp = new char *[capacity];
            memcpy(tmp, nums, i * sizeof(char *));
            delete[] nums;
            nums = tmp;
        }
        unsigned len = Random::lenDist(randomGenerator);
        nums[i] = new char[len + 1];

        for (int j = 0; j < len; ++j)
            // '0' + число — перевод числа в char
            // например, '0' + 1 = '1', поскольку '0' → код 48 и 48 + 1 → '1'
            nums[i][j] = Random::bitDist(randomGenerator) + '0';
    }

    return nums;
}

int main()
{
    for (unsigned test = 0; test < 1e6; ++test)
    {
        Measure localMes{1, 64};

        unsigned N = Random::countDist(Random::randomGenerator);
        char **nums = getData(N);

        unsigned maxSize = 0;
        for (unsigned i = 0; i < N; i++)
        {
            unsigned len = strlen(nums[i]);
            maxSize = (len > maxSize) ? len : maxSize;
        }

        radix(nums, N, maxSize);

        try
        {
            localMes.checkLimit();
        }
        catch (const runtime_error &e)
        {
            clear(nums, N);
            throw;
        }
    }
}
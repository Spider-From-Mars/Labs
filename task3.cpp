#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "Measure.hpp"

using namespace std;

/*
Задание 3.

Вам даны данные некоторого эксперимента X. По этим данным вам необходимо оценить два наиболее важных
момента - выборочное средее M(X) и выборочную дисперсию D(X). Выборочное среднее M(X) считается, как
среднее арифметическое всех чисел в выборке. Выборочная дисперсия равна среднему квадрату отклонения
величины от ее выборочного матожидания D(X)=M(X-M(X)). Путем нехитрых преобразований можно привести
эту формулу к более простой: D(X)=M(X 2 )-(M(X)) 2 , где X 2 - квадраты значений в выборке. Размер
выборки не превосходит 10^5 , величины не превосходят по модулю 1000.

Формат входных данных
На вход подается последовательность, оканчивающаяся 0 — данные эксперимента. Каждое число подается с
новой строки.

Формат выходных данных
Два числа через пробел — выборочное среднее и выборочная дисперсия.
*/

int main()
{
    ifstream file{"tests/task3.txt"};
    string buffer;

    Measure mes;

    double sum{0};
    double sumSquares{0};
    size_t size{0};

    while (getline(file, buffer))
    {
        if (buffer.empty())
            continue;

        if (buffer[0] == '#')
            continue;

        float sample = stof(buffer);
        if (sample == 0)
        {
            auto M = round(sum / size * 1000) / 1000;
            auto D = round(((sumSquares / size) - (M * M)) * 1000) / 1000;
            cout << M << ' ' << D << endl;

            sum = 0;
            sumSquares = 0;
            size = 0;

            continue;
        }

        sum += sample;
        sumSquares += sample * sample;
        size++;
    }

    mes.stop();
}
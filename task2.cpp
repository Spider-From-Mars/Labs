#include <fstream>
#include <iostream>
#include <string>

#include "Measure.hpp"

using namespace std;

/*
Задание 2.

На вход подается последовательность четырехзначных натуральных чисел из N элементов. Петя не любит,
когда число делится на 4, 7 и 9. Однако для каждого "деления" его ненависть пропадает, если
выполняются соответственно следующие условия: если число делится на 4, но начинается на 4 или 5;
если число делится на 7, но начинается на 7 или 1; если число делится на 9, но начинается на 9
или 8. Необходимо в введенной последовательности выявить неприятные Пете числа и вывести их на
экран. Если их нет — вывести 0.

Формат входных данных
Натуральное число N. На следующей строчке N четырехзначных натуральных чисел.

Формат выходных данных
Последовательность неприятных чисел. Либо 0, если таких чисел нет.
*/

int main()
{
    ifstream file{"tests/task2.txt"};
    string buffer;

    Measure mes;
    unsigned N{0};

    while (getline(file, buffer))
    {
        if (buffer.empty())
            continue;

        if (buffer[0] == '#')
            continue;

        N = stoi(buffer);
        unsigned curNum{0};
        bool wasBad{false};

        for (unsigned i = 0; i < N; ++i)
        {
            file >> curNum;
            bool isBadNum{false};

            unsigned short thousands = curNum / 1000;
            if (!(curNum % 4))
                isBadNum = (thousands == 4 || thousands == 5) ? false : true;

            if (!(curNum % 7))
                isBadNum = (thousands == 7 || thousands == 1) ? false : true;

            if (!(curNum % 9))
                isBadNum = (thousands == 9 || thousands == 8) ? false : true;

            if (isBadNum)
            {
                wasBad = isBadNum;
                cout << curNum << ' ';
            }
        }
        cout << (wasBad ? "" : "0") << endl;
        file.ignore();
    }

    mes.stop();
}
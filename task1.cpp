#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Measure.hpp"

using namespace std;

/*
Задание 1.

Васе задали два уравнения: a + x = b и c * x = d. Вася смог решить только одно из них, записал его
ответ. Но какое уравнение он решал? Преподаватель не растерялся, и решил поставить Васе 4, если его
ответ подойдет хоть к одному из уравнений, 5 если к обоим, 3 если Васин ответ = 1024 (и при этом не
является решением ни одного из уравнений, 1024 - любимое число преподавателя). Если же никакой из
этих вариантов не подходит, преподаватель поставит 2.

Формат входных данных

В первых четырех строках числа из условий: a, b, c, d, каждое в своей строке. В пятой строке — Васин
ответ. Все числа натуральные.

Формат выходных данных: Одно число — Васина оценка.
*/

int main()
{
    Measure mes;

    unsigned long a, b, c, d, answer;
    ifstream file{"tests/task1.txt"};
    string buffer;

    while (getline(file, buffer))
    {
        if (buffer.empty())
            continue;

        if (buffer[0] == '#')
            continue;

        // ф-ция getline() уже прочитала строку с первым числом,
        // поэтому надо извлечь его из буфера
        a = stoul(buffer);
        file >> b >> c >> d >> answer;

        bool eq1 = (a + answer == b);
        bool eq2 = (c * answer == d);

        unsigned short grade{2};
        if (eq1 && eq2)
            grade = 5;
        else if (eq1 || eq2)
            grade = 4;
        else if (answer == 1024)
            grade = 3;

        cout << "Итоговая оценка Васька: " << grade << endl;

        buffer.clear();
    }

    mes.stop();
}
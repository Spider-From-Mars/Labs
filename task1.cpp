#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Measure.hpp"

using namespace std;

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
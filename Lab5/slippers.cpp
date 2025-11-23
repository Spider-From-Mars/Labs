#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Measure.hpp"
#include "testGenerator.hpp"

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
обозначает левую тапку, а s обозначает правую тапку размера s).

Формат выходных данных Выведите одно число: минимальное расстояние между двумя тапочками одного
размера таких, что левая тапочка стоит левее правой. Если таких пар тапочек нет, то выведите одно
число 0
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

void solve(const string &test)
{
    istringstream iss{test};

    unsigned N;
    iss >> N;

    short *arr = new short[N];
    for (unsigned i = 0; i < N; ++i)
    {
        iss >> arr[i];
    }

    auto minDist = getDistance(arr, N);

    cout << "Минимальное расстояние = "
         << (minDist == numeric_limits<unsigned>::max() ? 0 : minDist) << endl;
    delete[] arr;
}

vector<string> collectTests(int N, const vector<Variable> &vars)
{
    vector<string> tests;

    streambuf *old_buf = cout.rdbuf();

    ostringstream capture;
    cout.rdbuf(capture.rdbuf());

    vector<string> cur(vars.size());
    Measure mes{N};
    generateAllRec(vars, 0, cur);
    mes.stop();

    cout.rdbuf(old_buf);

    cout << N << endl;
    mes.printStats();

    istringstream iss(capture.str());
    string line;
    while (getline(iss, line))
    {
        if (line.size() == 0)
            continue;

        tests.push_back(to_string(N) + "\n" + line + "\n");
    }

    return tests;
}

int main()
{
    constexpr unsigned short Nmin = 2, Nmax = 15;

    for (int N = Nmin; N <= Nmax; ++N)
    {
        vector<Variable> vars;
        for (int i = 1; i <= N; ++i)
        {
            vector<int> values;
            for (int x = -30; x <= -1; x++)
                values.push_back(x);
            for (int x = 1; x <= 30; x++)
                values.push_back(x);

            vars.push_back({"shoe" + to_string(i), VarType::ENUM_VALUES, EnumValues{values}});
        }

        for (const auto &test : collectTests(N, vars))
            solve(test);
    }
}
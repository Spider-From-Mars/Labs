#include <iostream>
#include <sstream>
#include <vector>

#include "Measure.hpp"
#include "testGenerator.hpp"

using namespace std;

/*
Задание 4.

Ограничение времени: 1 с
Ограничение памяти: 64M

На острове живут рыцари и лжецы, их дома расположены по кругу. Они очень любят делиться друг с
другом новостями, причём рыцарь говорит новость как услышал, а лжец перевирает. В нулевой день
приезжает путешественник и сообщает жителю дома №1 новость (ложную или истинную). На следующее утро
житель дома №1 сообщает её своему соседу из дома №2, на второй день житель дома №2 говорит новость
соседу из дома №3 и т.д. Если лжец говорит правду, он становится рыцарем, а если рыцарь говорит
ложь, он умирает вечером того же дня. Если сосед из дома i не находит соседа из дома i+1, он идёт к
следующему дому. Последний выживший сам с собой не разговаривает. Требуется узнать, кто останется на
острове через M дней распространения новости.

Формат входных данных

Первая строка — N, число жителей острова, через пробел 0 или 1 — истинность новости.
Далее N строк с описанием жителей, начиная с дома №1: имя и 0 или 1 — лжец или рыцарь.
M — число дней.

Формат выходных данных
Строки с описанием выживших, как во входных данных.
*/

struct Inhabitant
{
    string name;
    bool isKnight;
    bool alive = true;
};

void solve(int N, int M, bool newsTrue, Inhabitant *inhabitants)
{
    int current = 0;

    for (int day = 0; day < M; ++day)
    {
        // если current >= N, next начнется сначала
        int next = (current + 1) % N;
        while (!inhabitants[next].alive && next != current)
            // ищем следующего живого соседа по кругу
            next = (next + 1) % N;

        // если остался один живой — конец
        if (next == current)
            break;

        // если лжец — перевирает
        if (!inhabitants[current].isKnight)
            newsTrue = !newsTrue;

        // проверяем, как меняется статус текущего
        if (inhabitants[current].isKnight && !newsTrue)
        {
            inhabitants[current].alive = false; // рыцарь соврал — умер
        }
        else if (!inhabitants[current].isKnight && newsTrue)
        {
            inhabitants[current].isKnight = true; // лжец сказал правду — стал рыцарем
        }

        current = next; // на следующий день говорящий — сосед
    }

    for (int i = 0; i < N; ++i)
    {
        if (inhabitants[i].alive)
        {
            cout << inhabitants[i].name << ' ' << (inhabitants[i].isKnight ? 1 : 0) << endl;
        }
    }

    cout << endl;

    delete[] inhabitants;
}

vector<string> collectTests(int N, const vector<Variable> &vars)
{
    vector<string> lines;

    streambuf *oldbuf = cout.rdbuf();
    ostringstream capture;
    cout.rdbuf(capture.rdbuf());

    vector<string> cur(vars.size());
    Measure mes{N};
    generateAllRec(vars, 0, cur);
    mes.stop();

    cout.rdbuf(oldbuf);
    mes.printStats();

    istringstream iss(capture.str());
    string line;
    while (getline(iss, line))
        if (!line.empty())
            lines.push_back(line);

    return lines;
}

int main()
{
    constexpr unsigned short Nmin = 2, Nmax = 8;

    for (int N = Nmin; N <= Nmax; ++N)
    {
        vector<Variable> vars;

        vars.push_back({"newsTrue", VarType::INT_RANGE, IntRange{0, 1}});

        for (int i = 1; i <= N; ++i)
        {
            vars.push_back({"name" + to_string(i), VarType::STRING_VALUES,
                            StringValues{{"A", "B", "C", "D", "E"}}});

            vars.push_back({"role" + to_string(i), VarType::INT_RANGE, IntRange{0, 1}});
        }

        // M дней
        vars.push_back({"M", VarType::INT_RANGE, IntRange{0, 10}});

        for (const string &test : collectTests(N, vars))
        {
            stringstream ss(test);

            bool newsTrue;
            ss >> newsTrue;

            Inhabitant *inhabitants = new Inhabitant[N];
            for (int i = 0; i < N; ++i)
                ss >> inhabitants[i].name >> inhabitants[i].isKnight;

            int M;
            ss >> M;

            solve(N, M, newsTrue, inhabitants);
        }
    }
}

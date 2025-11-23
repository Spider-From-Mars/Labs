#include "testGenerator.hpp"

using namespace std;

// ============================
// Типичные тесты (min, mid, max)
// ============================
vector<vector<string>> generateTypical(const vector<Variable> &vars)
{
    vector<vector<string>> tests;

    vector<string> minCase, midCase, maxCase;

    for (const auto &v : vars)
    {
        switch (v.type)
        {

        case VarType::INT_RANGE:
        {
            auto r = get<IntRange>(v.data);
            int mid = (r.minVal + r.maxVal) / 2;
            minCase.push_back(to_string(r.minVal));
            midCase.push_back(to_string(mid));
            maxCase.push_back(to_string(r.maxVal));
            break;
        }

            // case VarType::DOUBLE_RANGE:
            // {
            //     auto r = get<DoubleRange>(v.data);
            //     double mid = (r.minVal + r.maxVal) / 2.0;
            //     minCase.push_back(to_string(r.minVal));
            //     midCase.push_back(to_string(mid));
            //     maxCase.push_back(to_string(r.maxVal));
            //     break;
            // }

        case VarType::ENUM_VALUES:
        {
            auto e = get<EnumValues>(v.data);
            minCase.push_back(to_string(e.values.front()));
            midCase.push_back(to_string(e.values[e.values.size() / 2]));
            maxCase.push_back(to_string(e.values.back()));
            break;
        }

        case VarType::STRING_VALUES:
        {
            auto s = get<StringValues>(v.data);
            minCase.push_back(s.values.front());
            midCase.push_back(s.values[s.values.size() / 2]);
            maxCase.push_back(s.values.back());
            break;
        }

        case VarType::BOOL_TYPE:
            minCase.push_back("false");
            midCase.push_back("true"); // не имеет mid, но пусть true
            maxCase.push_back("true");
            break;
        }
    }

    tests.push_back(minCase);
    tests.push_back(midCase);
    tests.push_back(maxCase);

    return tests;
}

// ============================
// Генерация всех комбинаций
// ============================
void generateAllRec(const vector<Variable> &vars, int idx, vector<string> &cur)
{
    // Базовый случай рекурсии
    if (idx == vars.size())
    {
        for (auto &s : cur)
            cout << s << " ";
        cout << "\n";

        return;
    }

    const auto &v = vars[idx];

    switch (v.type)
    {

    case VarType::INT_RANGE:
    {
        auto r = get<IntRange>(v.data);
        for (int x = r.minVal; x <= r.maxVal; ++x)
        {
            cur[idx] = to_string(x);
            generateAllRec(vars, idx + 1, cur);
        }
        break;
    }

        // case VarType::DOUBLE_RANGE:
        // {
        //     auto r = get<DoubleRange>(v.data);
        //     for (double x = r.minVal; x <= r.maxVal + 1e-12; x += r.step)
        //     {
        //         cur[idx] = to_string(x);
        //         generateAllRec(vars, idx + 1, cur);
        //     }
        //     break;
        // }

    case VarType::ENUM_VALUES:
    {
        auto e = get<EnumValues>(v.data);
        for (int v : e.values)
        {
            cur[idx] = to_string(v);
            generateAllRec(vars, idx + 1, cur);
        }
        break;
    }

    case VarType::STRING_VALUES:
    {
        auto s = get<StringValues>(v.data);
        for (auto &st : s.values)
        {
            cur[idx] = st;
            generateAllRec(vars, idx + 1, cur);
        }
        break;
    }

    case VarType::BOOL_TYPE:
        cur[idx] = "false";
        generateAllRec(vars, idx + 1, cur);
        cur[idx] = "true";
        generateAllRec(vars, idx + 1, cur);
        break;
    }
}
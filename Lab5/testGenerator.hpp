#include <cmath>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

// ============================
// Типы переменных
// ============================
enum class VarType
{
    INT_RANGE,
    // DOUBLE_RANGE,
    ENUM_VALUES,
    STRING_VALUES,
    BOOL_TYPE
};

// ============================
// Структуры параметров
// ============================
struct IntRange
{
    int minVal;
    int maxVal;
};

// DELETE ============
// struct DoubleRange
// {
//     double minVal;
//     double maxVal;
//     double step;
// };
// END DELETE ============

struct EnumValues
{
    std::vector<int> values;
};

struct StringValues
{
    std::vector<std::string> values;
};

struct BoolType
{
}; // без параметров

// Универсальное описание переменной
struct Variable
{
    std::string name;
    VarType type;
    std::variant<IntRange, EnumValues, StringValues, BoolType> data;
};

// ============================
// Подсчёт количества входов
// ============================
// DELETE ============
// long long countTotal(const std::vector<Variable> &vars);
// END DELETE ============

// ============================
// Типичные тесты (min, mid, max)
// ============================
std::vector<std::vector<std::string>> generateTypical(const std::vector<Variable> &vars);

// ============================
// Генерация всех комбинаций
// ============================
void generateAllRec(const std::vector<Variable> &vars, int idx, std::vector<std::string> &cur);
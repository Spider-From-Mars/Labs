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
    DOUBLE_RANGE,
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

struct DoubleRange
{
    double minVal;
    double maxVal;
    double step;
};

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
    std::variant<IntRange, DoubleRange, EnumValues, StringValues, BoolType> data;
};

// ============================
// Подсчёт количества входов
// ============================
long long countTotal(const std::vector<Variable> &vars);

// ============================
// Типичные тесты (min, mid, max)
// ============================
std::vector<std::vector<std::string>> generateTypical(const std::vector<Variable> &vars);

// ============================
// Генерация всех комбинаций
// ============================
void generateAllRec(const std::vector<Variable> &vars, int idx, std::vector<std::string> &cur);
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Measure.hpp"

using namespace std;

/*
Задание 1

Поворот 2d массива

Ограничение времени: 5 с
Ограничение памяти: 64M

Повернуть двумерный массив на 90 градусов по часовой стрелке.

Формат входных данных
На первой строке размерность массива N, N < 1000. На следующих N строках матрица размера N x N.
Числа разделены пробелами. Каждый элемент - целое число, помещающееся в 4 байта.

Формат выходных данных
Матрица, повернутая на 90 градусов по часовой стрелке.
*/

void printMatrix(int **matrix, unsigned short rows, unsigned short cols)
{
    for (unsigned short i = 0; i < rows; ++i)
    {
        for (unsigned short j = 0; j < cols; ++j)
        {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

void clearMemory(int **matrix, unsigned short rows)
{
    for (unsigned short i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main()
{
    Measure mes;

    ifstream file{"tests/task1.txt"};
    string buffer;

    while (getline(file, buffer))
    {
        Measure localMes{5, 64};

        if (buffer.empty())
            continue;

        if (buffer[0] == '#')
            continue;

        const unsigned short N = stoi(buffer);
        int **matrix = new int *[N];

        // Так как в основном цикле требуется полностью выделенная память (обращение к последующим
        // строкам), то здесь аллоцируется вся необходимая память
        for (unsigned short i = 0; i < N; ++i)
            matrix[i] = new int[N];

        for (unsigned short i = 0; i < N; ++i)
        {
            getline(file, buffer);

            istringstream iss(buffer);

            int num;
            unsigned short j{0};
            while (iss >> num)
            {
                if (j < N)
                {
                    matrix[j++][N - i - 1] = num;
                }
                else
                {
                    throw runtime_error(
                        "Ошибка: количество введённых элементов превышает заданное значение!");
                }
            }
        }

        printMatrix(matrix, N, N);
        cout << endl;

        clearMemory(matrix, N);
        localMes.checkLimit();
    }

    mes.stop();
}
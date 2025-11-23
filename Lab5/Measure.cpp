#include "Measure.hpp"

Measure::Measure(long long testsNum)
    : startTime{std::chrono::high_resolution_clock::now()}, N(testsNum), time(3), memory(3)
{
}

void Measure::stop()
{
    auto duration =
        std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime)
            .count();

    if (duration < time[0])
        time[0] = duration;
    if (duration > time[2])
        time[2] = duration;

    time[1] = duration / N;

    long curMem = getMemoryUsage() / 1024.f / 1024.f;

    if (curMem < memory[0])
        memory[0] = curMem;
    if (curMem > memory[2])
        memory[2] = curMem;

    memory[1] = curMem / N;
}

void Measure::printStats()
{
    std::cout << "Наименьшее время: " << time[0] << " сек." << std::endl;
    std::cout << "Среднее время: " << time[1] << " сек." << std::endl;
    std::cout << "Наибольшее время: " << time[2] << " сек." << std::endl << std::endl;

    std::cout << "Наименьшая память: " << memory[0] << " МБ" << std::endl;
    std::cout << "Средняя память: " << memory[1] << " МБ" << std::endl;
    std::cout << "Наибольшая память: " << memory[2] << " МБ" << std::endl << std::endl;
}

long Measure::getMemoryUsage()
{
    // Возвращает общий пик (максимум) потребления резидентной памяти процесса
    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == 0)
        return usage.ru_maxrss;

    return 0;
}
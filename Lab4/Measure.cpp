#include "Measure.hpp"

Measure::Measure() : start{std::chrono::high_resolution_clock::now()} {}

Measure::Measure(double seconds, long memory)
    : start{std::chrono::high_resolution_clock::now()}, timeLimit{seconds}, memoryLimit{memory}
{
}

void Measure::stop()
{
    auto duration =
        std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

    std::cout << "Затрачено времени: " << duration << " сек." << std::endl;
    std::cout << "Использовано памяти: " << getMemoryUsage() / 1024.f / 1024.f << " МБ"
              << std::endl;
}

void Measure::checkLimit()
{
    auto duration =
        std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

    if (duration > timeLimit)
        throw std::runtime_error("Time limit exceeded");

    auto memory = getMemoryUsage() / 1024.f / 1024.f;

    if (memory > memoryLimit)
        throw std::runtime_error("Memory limit exceeded");
}

long Measure::getMemoryUsage()
{
    // Возвращает общий пик (максимум) потребления резидентной памяти процесса
    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == 0)
        return usage.ru_maxrss;

    return 0;
}
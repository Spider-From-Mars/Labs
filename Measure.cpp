#include "Measure.hpp"

Measure::Measure() : start{std::chrono::high_resolution_clock::now()} {}

void Measure::stop()
{
    auto duration =
        std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

    std::cout << "Затрачено времени: " << duration << " сек." << std::endl;
    std::cout << "Использовано памяти: " << getMemoryUsage() / 1024.f / 1024.f << " МБ"
              << std::endl;
}

long Measure::getMemoryUsage()
{
    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == 0)
        return usage.ru_maxrss;

    return 0;
}
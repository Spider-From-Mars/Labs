#include <chrono>
#include <iostream>
#include <sys/resource.h>
#include <vector>

class Measure
{
  public:
    Measure(long long testsNum);

    void stop();
    void printStats();

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    long long N;
    std::vector<double> time;
    std::vector<long> memory;

    long getMemoryUsage();
};

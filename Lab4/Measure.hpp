#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sys/resource.h>

class Measure
{
  public:
    Measure();
    Measure(double seconds, long memory);

    void stop();
    void checkLimit();

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    double timeLimit;
    long memoryLimit;

    long getMemoryUsage();
};

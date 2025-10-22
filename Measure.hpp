#include <chrono>
#include <fstream>
#include <iostream>
#include <sys/resource.h>

class Measure
{
  public:
    Measure();

    void stop();

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    long getMemoryUsage();
};

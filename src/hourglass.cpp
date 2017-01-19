#include "hourglass.hpp"


std::chrono::system_clock::time_point hourglass::now()
{
    return std::chrono::high_resolution_clock::now();
}

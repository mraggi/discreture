#pragma once

#include <chrono>
#include <ctime>

namespace discreture
{
// You probably want something else, but whatever.

using time_point_t = std::chrono::time_point<std::chrono::steady_clock>;

inline double elapsed_seconds(time_point_t from, time_point_t to)
{
    using seconds = std::chrono::duration<double>;
    return std::chrono::duration_cast<seconds>(to - from).count();
}

class Chronometer
{
public:
    Chronometer() : start_(std::chrono::steady_clock::now()) {}

    double Reset()
    {
        auto previous = start_;
        start_ = std::chrono::steady_clock::now();

        return elapsed_seconds(previous, start_);
    }

    double Peek() const
    {
        auto now = std::chrono::steady_clock::now();

        return elapsed_seconds(start_, now);
    }

    time_point_t start_;
};

} // namespace discreture

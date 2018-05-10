#pragma once

#include <chrono>
#include <ctime>

namespace dscr
{
// You probably want something else, but whatever.
// TODO(mraggi): Use a better method of casting to double rather than measure in
// microseconds and the multiply by 1/1M, which is stupid.

inline double diffclock(clock_t a, clock_t b)
{
    const double c = 1.0/CLOCKS_PER_SEC;
    return double(a - b)*c;
}

using clockt = std::chrono::time_point<std::chrono::steady_clock>;

inline double diffclockt(clockt a, clockt b)
{

    const double t = 0.000001;
    return std::chrono::duration_cast<std::chrono::microseconds>(a - b)
             .count() *
      t;
}

class RClock
{
public:
    static RClock& Instance()
    {
        static RClock A;
        return A;
    }

    std::chrono::time_point<std::chrono::steady_clock> start_timer;

private:
    RClock() : start_timer(std::chrono::steady_clock::now()) {}
};

class Chronometer
{
public:
    Chronometer() : m_timer(std::chrono::steady_clock::now()) {}

    double Reset()
    {
        auto tlast = m_timer;
        m_timer = std::chrono::steady_clock::now();

        return std::chrono::duration_cast<std::chrono::duration<double>>(
                 m_timer - tlast)
          .count();
    }

    double Peek() const
    {
        auto tnow = std::chrono::steady_clock::now();

        return std::chrono::duration_cast<std::chrono::duration<double>>(
                 tnow - m_timer)
          .count();
    }

    std::chrono::time_point<std::chrono::steady_clock> m_timer;
};

inline double TimeFromStart()
{
    auto tnow = std::chrono::steady_clock::now();

    return diffclockt(tnow, RClock::Instance().start_timer);
}
} // namespace dscr

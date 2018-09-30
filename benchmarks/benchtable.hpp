
#pragma once

#include "Discreture/TimeHelpers.hpp"
#include "benchmarker.hpp"
#include "do_not_optimize.hpp"
#include "external/rang.hpp"
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const int columntime = 35;
const int columnsize = 50;
const int columnspeed = 70;

struct BenchRow
{
    BenchRow() = default;
    BenchRow(std::string Name, double t, size_t cs)
        : name(std::move(Name)), avg_time(t), container_size(cs)
    {}

    static void print_header(std::ostream& os)
    {
        const std::string head1 = "Benchmark name";
        const std::string head2 = "Time";
        const std::string head3 = "# processed";
        const std::string head4 = "Speed";

        os << head1;

        for (int i = head1.size(); i < columntime + 2; ++i)
            os << ' ';
        os << head2;

        for (int i = columntime + head2.size() + 2; i < columnsize; ++i)
            os << ' ';
        os << head3;

        for (int i = columnsize + head3.size(); i <= columnspeed + 6; ++i)
            os << ' ';
        os << head4;

        os << std::endl;
    }

    static void print_line(std::ostream& os)
    {
        for (int i = 0; i < columnspeed + 17; ++i)
            os << '-';
        os << std::endl;
    }

    double speed() const
    {
        return static_cast<double>(container_size)/avg_time;
    }

    std::string name{""};
    double avg_time{0.0};
    size_t container_size{0};
    bool variable_time_units{false};
};

inline std::ostream& operator<<(std::ostream& os, const BenchRow& T)
{
    // 	os << '|';
    os << T.name;
    for (int i = T.name.size(); i < columntime; ++i)
        os << ' ';
    // 	os << '|';
    double avg_time = T.avg_time;
    std::string units = "s";
    auto color = rang::fg::magenta;

    if (T.variable_time_units)
    {
        if (avg_time < 0.01)
        {
            avg_time *= 1000;
            units = "ms";
            color = rang::fg::yellow;
        }

        if (avg_time < 0.01)
        {
            avg_time *= 1000;
            units = "μs";
            color = rang::fg::green;
        }
    }

    const int precision = 3;
    const int timewidth = 6;
    os << std::setprecision(precision) << std::fixed << color;
    os << std::setw(timewidth) << avg_time << units << rang::fg::reset;

    for (int i = columntime + units.size() + timewidth; i <= columnsize; ++i)
        os << ' ';
    // 	os << '|';

    const int sizewidth = 10;
    os << rang::fg::blue << std::setw(sizewidth) << T.container_size
       << rang::fg::reset;

    for (int i = columnsize + sizewidth; i <= columnspeed; ++i)
        os << ' ';
    // 	os << '|';

    auto speed_color = rang::fg::green;
    if (T.speed() < 5e8)
        speed_color = rang::fg::cyan;
    if (T.speed() < 1e8)
        speed_color = rang::fg::yellow;
    if (T.speed() < 1e7)
        speed_color = rang::fg::red;

    os << std::setprecision(3) << std::scientific << speed_color;

    if (T.speed() > 1e9)
        os << rang::fgB::green << rang::style::bold;

    os << T.speed() << " #/sec" << rang::fg::reset << rang::style::reset
       << std::endl;

    return os;
}

template <class Container>
BenchRow ProduceRowForward(std::string name, const Container& A)
{
    double t = FWIterationBenchmark(A);

    name += " Forward";

    return BenchRow(name, t, A.size());
}

template <class Container>
BenchRow ProduceRowParallelForward(std::string name,
                                   const Container& A,
                                   int num_processors = 4)
{
    double t = ParallelBenchmark(A, num_processors);
    using namespace std::string_literals;
    name += " Parallel w/ "s + std::to_string(num_processors) + " threads"s;

    return BenchRow(name, t, A.size());
}

template <class Container>
BenchRow ProduceRowReverse(std::string name, const Container& A)
{
    double t = ReverseIterationBenchmark(A);

    name += " Reverse";

    return BenchRow(name, t, A.size());
}

template <class Container>
BenchRow ProduceRowForEach(std::string name, const Container& A)
{
    double t = ForEachBenchmark(A);

    name += " for_each";

    return BenchRow(name, t, A.size());
}

template <class Container>
BenchRow ProduceRowConstruct(std::string name,
                             const Container& A,
                             int numtimes = 100000)
{
    double t = ConstructionBenchmark(A, numtimes);

    name += " Construct";

    return BenchRow(name, t, numtimes);
}

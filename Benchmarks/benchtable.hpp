#pragma once

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <iomanip>
#include "do_not_optimize.hpp"
#include "TimeHelpers.hpp"
#include "external/rang.hpp"
#include "benchmarker.hpp"

const int columntime = 32;
const int columnsize = 46;
const int columnspeed = 66;

struct TableRow
{
	TableRow() {} // empty initializer
	TableRow(const std::string& Name, double t, size_t cs) : name(Name), avg_time(t), container_size(cs)  {} 
	
	static void print_header(std::ostream& os)
	{
		const std::string head1 = "Test name";
		const std::string head2 = "Time";
		const std::string head3 = "# processed";
		const std::string head4 = "Speed";
		
		os << head1;
		
		for (int i = head1.size(); i < columntime; ++i) os << ' ';
		os << head2;
		
		for (int i = columntime+head2.size(); i <= columnsize; ++i) os << ' ';
		os << head3;
		
		for (int i = columnsize+head3.size(); i <= columnspeed; ++i) os << ' ';
		os << head4;
		
		os << std::endl;
	}
	
	static void print_line(std::ostream& os)
	{
		os << "-----------------------------------------------------------------------------------" << std::endl;
	}
	
	double speed() const
	{
		return static_cast<double>(container_size)/avg_time;
	}
	
	std::string name {""};
	double avg_time {0.0};
	size_t container_size {0};
	bool variable_time_units {false};
};

std::ostream& operator<<(std::ostream& os, const TableRow& T)
{
	os << T.name;
	for (int i = T.name.size(); i < columntime; ++i) 
		os << ' ';
	
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
	
	const int precision = 4;
	os << std::setprecision(precision) << std::fixed << color;
	os << T.avg_time << units << rang::fg::reset;
	
	for (int i = columntime+units.size()+precision; i < columnsize; ++i) 
		os << ' ';
	
	os << rang::fg::cyan << T.container_size << rang::fg::reset;
	
	for (int i = columnsize + std::to_string(T.container_size).size(); i < columnspeed; ++i) 
		os << ' ';
	
	auto speed_color = rang::fg::green;
	if (T.speed() < 1e8)
		speed_color = rang::fg::yellow;
	if (T.speed() < 1e7)
		speed_color = rang::fg::red;
	
	
	os << std::setprecision(3) << std::scientific << speed_color << T.speed() << " #/sec" << rang::fg::reset << std::endl;
	
	return os;
}

using Table = std::vector<TableRow>;

template <class Container>
TableRow ProduceRowForward(std::string name, const Container& A)
{
	double t = FWIterationBenchmark(A);

	name += " Forward";
	
	return TableRow(name, t, A.size());
}

template <class Container>
TableRow ProduceRowReverse(std::string name, const Container& A)
{
	double t = ReverseIterationBenchmark(A);

	name += " Reverse";
	
	return TableRow(name, t, A.size());
}

template <class Container>
TableRow ProduceRowForEach(std::string name, const Container& A)
{
	double t = ForEachBenchmark(A);

	name += " for_each";
	
	return TableRow(name, t, A.size());
}

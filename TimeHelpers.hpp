#pragma once

#include <ctime>
#include <chrono>


namespace dscr
{
	// You probably want something else, but whatever.

	inline double diffclock(clock_t a, clock_t b)
	{
		const double c = 1.0/CLOCKS_PER_SEC;
		return double(a-b)*c;
	}
	
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> clockt;
	
	inline double diffclockt(clockt a, clockt b)
	{
		
		const double t = 0.000001;
		return std::chrono::duration_cast<std::chrono::microseconds>(a-b).count()*t;
	}
	
	class RClock
	{
	public:
		static RClock& Instance()
		{
			static RClock A;
			return A;
		}
		
		std::chrono::time_point<std::chrono::high_resolution_clock> start_timer;
		
		
	private:
		RClock() : start_timer(std::chrono::high_resolution_clock::now()) {}
	};

	class Chronometer
	{
	public:
		Chronometer() : m_timer(std::chrono::high_resolution_clock::now()) {}
		
		double Reset()
		{
			auto tlast = m_timer;
			m_timer = std::chrono::high_resolution_clock::now();
		
			return diffclockt(m_timer, tlast);
		}
		
		double Peek() const
		{
			auto tnow = std::chrono::high_resolution_clock::now();
		
			return diffclockt(tnow, m_timer);
		}
		
		std::chrono::time_point<std::chrono::high_resolution_clock> m_timer;
	};

	inline double TimeFromStart()
	{
		auto tnow = std::chrono::high_resolution_clock::now();
		
		return diffclockt(tnow, RClock::Instance().start_timer);
	}
}

#pragma once

#include <chrono>
#include "lwlog/print.h"

class Benchmark
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;

private:
	void stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		lwlog::print("{0}us\n", duration);
	}

public:
	Benchmark()
	{
		m_startTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Benchmark()
	{
		stop();
	}
};
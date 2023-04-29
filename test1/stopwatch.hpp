#pragma once

#include <chrono>

struct Stopwatch
{
	long startTime;

	void start()
	{
		auto t = std::chrono::system_clock::now() - std::chrono::system_clock::time_point::min();
		startTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t).count();
	}

	double time()
	{
		auto t = std::chrono::system_clock::now() - std::chrono::system_clock::time_point::min();
		return (std::chrono::duration_cast<std::chrono::nanoseconds>(t).count() - startTime) / 1000000000.0;
	}
};
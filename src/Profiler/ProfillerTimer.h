#ifndef PROFILLER_TIME_H
#define PROFILLER_TIME_H

#include <string>
#include <chrono>

class ProfilerTime
{
public:
	ProfilerTime(std::string _name);
	~ProfilerTime();
private:

	std::string m_name;
	std::chrono::high_resolution_clock::time_point start;
};

#endif // !PROFILLER_TIME_H

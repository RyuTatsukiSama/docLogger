#ifndef PROFILER_H
#define PROFILER_H

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <fstream>
#include "TraceEvent.h"

class Profiler
{
public:
	Profiler() {}
	~Profiler() {}
	static Profiler* GetInstance();
	void Trace(std::string _name, std::string _phase, std::chrono::microseconds _ts, std::thread::id _tid, int _pid);
	void SaveTrace(std::string _nameOutput);

	std::chrono::high_resolution_clock::time_point f0 = std::chrono::high_resolution_clock::now();

private:
	static Profiler* instance;

	std::vector<TraceEvent> traceEvents;
	std::string outputName = "Profiler.json";
};

#endif // !PROFILER_H

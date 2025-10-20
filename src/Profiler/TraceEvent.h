#ifndef TRACE_EVENT_H
#define TRACE_EVENT_H

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

typedef struct TraceEvent 
{
	std::string name;
	std::string phase;
	std::chrono::microseconds timeStamp;
	std::thread::id threadID;
	int pid;
};

#endif // !TRACE_EVENT_H


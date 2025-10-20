#include "Profiler.h"

void Profiler::SaveTrace(std::string _nameOutput)
{
	std::ofstream output(_nameOutput, std::ios::out);
	if (!output.is_open())
	{
		std::cerr << "Error: could not open " << _nameOutput << std::endl;
	}

	output << "{\n \"traceEvents\": [\n";

	for (size_t i = 0; i < traceEvents.size(); i++)
	{
		const TraceEvent& event = traceEvents[i];
		output << "		{";
		output << "\"name\":\"" << event.name << "\",";
		output << "\"ph\":\"" << event.phase << "\",";
		output << "\"ts\":\"" << event.timeStamp.count() << "\",";
		output << "\"tid\":\"" << event.threadID << "\",";
		output << "\"pid\":" << event.pid;
		output << "}";

		if (i + 1 < traceEvents.size())
			output << ",";
		output << "\n";
	}

	output << "]\n}\n";
	output.close();
}

Profiler* Profiler::instance = nullptr;

Profiler* Profiler::GetInstance()
{
	if (instance == nullptr)
		instance = new Profiler();
	return instance;
}

void Profiler::Trace(std::string _name, std::string _phase, std::chrono::microseconds _ts, std::thread::id _tid, int _pid)
{
	TraceEvent event{
		.name = _name,
		.phase = _phase,
		.timeStamp = _ts,
		.threadID = _tid,
		.pid = _pid
	};

	traceEvents.push_back(event);
}

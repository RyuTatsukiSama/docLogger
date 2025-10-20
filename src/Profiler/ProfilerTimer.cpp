#include "ProfillerTimer.h"
#include "Profiler.h"

ProfilerTime::ProfilerTime(std::string _name) : m_name(_name)
{
	start = std::chrono::high_resolution_clock::now();
	Profiler::GetInstance()->Trace(_name, "B", duration_cast<std::chrono::microseconds>(start - Profiler::GetInstance()->f0), std::this_thread::get_id(), _getpid());
}

ProfilerTime::~ProfilerTime()
{
	const std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	const std::chrono::microseconds duration = duration_cast<std::chrono::microseconds>(end - start);
	std::cout << m_name << " take " << duration.count() * 1e-3f << " ms" << std::endl;

	Profiler::GetInstance()->Trace(m_name, "E", duration_cast<std::chrono::microseconds>(end - Profiler::GetInstance()->f0), std::this_thread::get_id(), _getpid());
}

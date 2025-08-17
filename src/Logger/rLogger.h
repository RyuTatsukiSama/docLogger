#ifndef RLOGGER_H
#define RLOGGER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string_view>
#include <functional>
#include <unordered_map>
#include <format>
#include <thread>
#include <ctime>

struct rLogSeverity
{
	int value;

	static const rLogSeverity LOG, DEBUG, INFO, WARNING, ERROR, CRITICAL;
};

thread_local static std::string threadName; // ! rename this variable

class rLogger
{
protected:
	rLogSeverity severityThreshdold = rLogSeverity::LOG;
	std::vector<std::ostream *> outputStreams;
	static std::unordered_map<rLogSeverity, std::string> severityText;

	std::string FormatLog(const rLogSeverity &_severity, const std::string _message);
	void ColorConsole(const rLogSeverity &_severity);

public:
	rLogger(std::string _threadName = "Main");
	~rLogger() = default;

	void Log(const rLogSeverity &_severity, const std::string &_message);
	void RegisterOutputStream(const std::ofstream &_stream);

#ifdef RTESTING
	std::string GetFormatLog(const rLogSeverity &_severity, const std::string _message)
	{
		FormatLog(_severity, _message);
	}
#endif
};
#endif // !RLOGGER_H
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
#include <chrono>
#include <Windows.h>

#include "rLoggerOptions.h"

struct rLoggerSeverity
{
	int value;

	static const rLoggerSeverity Log, Debug, Info, Warning, Error, Critical;
};

thread_local static std::string threadName; // ! rename this variable

class rLogger
{
protected:
	rLoggerSeverity severityThreshdold = rLoggerSeverity::Log;
	std::vector<std::ostream *> outputStreams;
	static std::unordered_map<int, std::string> severityText;

	std::string FormatLog(const rLoggerSeverity &_severity, const std::string _message);
	void ColorConsole(const rLoggerSeverity &_severity);

public:
	rLogger(std::string _threadName);
	rLogger(rLoggerOptions _options);
	~rLogger();

	void Log(const rLoggerSeverity &_severity, const std::string &_message);
	void RegisterOutputStream(std::ostream *_stream);

#ifdef RTESTING
	std::string GetFormatLog(const rLogSeverity &_severity, const std::string _message)
	{
		return FormatLog(_severity, _message);
	}
#endif
};
#endif // !RLOGGER_H
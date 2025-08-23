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
#include <filesystem>

#include "rLoggerOptions.h"
#include "rLoggerSeverity.h"

namespace r
{
	thread_local static std::string threadName; // ! rename this variable
};

class rLogger
{
protected:
	rLoggerSeverity severityThreshdold = rLoggerSeverity::Trace;
	std::vector<std::ostream *> outputStreams;

	static const std::unordered_map<rLoggerSeverity, std::string> &getSeverityText();
	static const std::unordered_map<rLoggerSeverity, std::string> &getSeverityColor();

	std::string FormatLog(const rLoggerSeverity &_severity, const std::string _message);

public:
	rLogger(rLoggerOptions _options);
	~rLogger();

	void Log(const rLoggerSeverity &_severity, const std::string &_message);
	void RegisterOutputStream(std::ostream *_stream);

#pragma region Severity Functions

	void Trace(const std::string &_message);
	void Debug(const std::string &_message);
	void Info(const std::string &_message);
	void Warning(const std::string &_message);
	void Error(const std::string &_message);
	void Critical(const std::string &_message);

#pragma endregion

#ifdef RTESTING
	std::string GetFormatLog(const rLoggerSeverity &_severity, const std::string _message)
	{
		return FormatLog(_severity, _message);
	}
#endif
};
#endif // !RLOGGER_H
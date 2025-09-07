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
#include <source_location>
#include <mutex>

#include "rLoggerOptions.h"
#include "rLoggerSeverity.h"

namespace r
{
	thread_local static std::string threadName;
	static std::mutex lock;
};

class rLogger
{
protected:
	rLoggerSeverity severityThreshdold = rLoggerSeverity::Trace;
	std::vector<std::ostream *> outputStreams;
	std::vector<std::function<void(const std::string)>> logCallbacks;

	std::function<std::chrono::system_clock::time_point()> timeProvider;

	static const std::unordered_map<rLoggerSeverity, std::string> &getSeverityText();
	static const std::unordered_map<rLoggerSeverity, std::string> &getSeverityColor();

	std::string FormatLog(const rLoggerSeverity &_severity, const std::string _message);

public:
	rLogger(std::string _threadName = "Main");
	~rLogger() = default;

	void Log(const rLoggerSeverity &_severity, const std::string &_message);
	void RegisterOutputStream(std::ostream *_stream);
	void RegisterLogCallback(std::function<void(const std::string)> _callback);

	void Caller(const std::source_location &where = std::source_location::current());

#pragma region Severity Functions

	void Trace(const std::string &_message);
	void Debug(const std::string &_message);
	void Info(const std::string &_message);
	void Warning(const std::string &_message);
	void Error(const std::string &_message);
	void Critical(const std::string &_message);

#pragma endregion
};
#endif // !RLOGGER_H
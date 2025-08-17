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
	std::vector<std::ofstream *> outputStreams;

	std::string FormatLog(const rLogSeverity &_severity, const std::string _message);

public:
	rLogger(std::string _threadName = "Main");
	~rLogger() = default;

	void Log(const rLogSeverity &_severity, const std::string &_message);
	void RegisterOutputStream(const std::ofstream &_stream);
};
#endif // !RLOGGER_H
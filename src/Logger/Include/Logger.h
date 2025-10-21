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

#include "LoggerOptions.h"
#include "LoggerSeverity.h"

namespace doc
{
	extern thread_local std::string threadName;
	static std::mutex lock;

	class Logger
	{
	protected:
		/// @brief Use to prevent log with a severity below to be register
		LoggerSeverity severityThreshdold = LoggerSeverity::Trace;

		/// @brief Vector of the streams the log message are sent
		std::vector<std::ostream *> outputStreams;

		/// @brief Vector of the callbacks with the formatted message
		std::vector<std::function<void(const std::string)>> logCallbacks;

		/// @brief The function wich return the time stamp
		std::function<std::chrono::system_clock::time_point()> timeProvider;

		/// @brief Use to access the unordered_map wich contain the text link to loggerSeverity
		static const std::unordered_map<LoggerSeverity, std::string> &getSeverityText();

		/// @brief Use to access the unordered_map wich contain the color link to loggerSeverity
		static const std::unordered_map<LoggerSeverity, std::string> &getSeverityColor();

		/// @brief Create the clean formated log message with severity, timestamp, thread name and message
		/// @param _severity Severity of the log
		/// @param _message Message you want to be in the log
		/// @return The clean log message in a std::string
		std::string FormatLog(const LoggerSeverity &_severity, const std::string _message);

		/// @brief The options of the logger
		LoggerOptions lOpts;

	public:
		/// @brief Constructor with thread name and options
		/// @param _threadName The name of the thread where this logger is used
		/// @param _options The options you want to use for this logger
		Logger(const std::string &_threadName, const LoggerOptions &_options);

		/// @brief Constructor with only thread name, use the gOpts as options
		/// @param _threadName The name of the thread where this logger is used
		Logger(const std::string &_threadName);

		/// @brief Constructor with only options, use " Main " as thread name
		/// @param _options The options you want to use for this logger
		Logger(const LoggerOptions &_options);

		/// @brief Default constructor, use the gOpts as options and " Main " as thread name
		Logger();

		/// @brief Default destructor, close all the streams
		~Logger() = default;

		/// @brief The standard method to create a log
		/// @param _severity Severity of the log
		/// @param _message Message you want to be in the log
		void Log(const LoggerSeverity &_severity, const std::string &_message);

		/// @brief Add a stream where the log will be sent to
		/// @param _stream The stream you want to add
		void RegisterOutputStream(std::ostream *_stream);

		/// @brief Use it if you want to display the formatted message, but not with a stream
		/// Warning the ANSI code for the color are not present in this string
		/// @param _callback The function/lambda/method that will use the formatted message, with a std::string parameters
		void RegisterLogCallback(std::function<void(const std::string)> _callback);

		/// @brief Create a Debug severity Log whith the name of the function which call this method
		/// @param _where No need to touch it, if you do the method risk to not work properly
		void Caller(const std::source_location &_where = std::source_location::current());

		void setSeverityThreshdold(const LoggerSeverity &_severity);

#pragma region Severity Methods

		/// @brief Make a log with the severity " Trace " automatically
		/// @param _message The message you want in your log
		void Trace(const std::string &_message);

		/// @brief Make a log with the severity " Debug " automatically
		/// @param _message The message you want in your log
		void Debug(const std::string &_message);

		/// @brief Make a log with the severity " Info " automatically
		/// @param _message The message you want in your log
		void Info(const std::string &_message);

		/// @brief Make a log with the severity " Warning " automatically
		/// @param _message The message you want in your log
		void Warning(const std::string &_message);

		/// @brief Make a log with the severity " Error " automatically
		/// @param _message The message you want in your log
		void Error(const std::string &_message);

		/// @brief Make a log with the severity " Critical " automatically
		/// @param _message The message you want in your log
		void Critical(const std::string &_message);

#pragma endregion
	};
}
#endif // !RLOGGER_H
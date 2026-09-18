#include "doc/Logger.h"
#include <filesystem>
#include <format>

namespace doc
{
	thread_local std::string threadName = "";

	DLL_API const std::string &getThreadName()
	{
		return threadName;
	}

#pragma region docLogger Class
#pragma region Protected

	const std::string Logger::getSeverityTextAt(const LoggerSeverity &_severity)
	{
		return severityText.at(_severity);
	}

	void Logger::initSeverityMap()
	{
		severityText = {
			{LoggerSeverity::Trace, "\x1B[45mTRACE\x1B[0m"}, // NOSONAR
			{LoggerSeverity::Debug, "\x1B[44mDEBUG\x1B[0m"}, // NOSONAR
			{LoggerSeverity::Info, "\x1B[42mINFO\x1B[0m"}, // NOSONAR
			{LoggerSeverity::Warning, "\x1B[43mWARNING\x1B[0m"}, // NOSONAR
			{LoggerSeverity::Error, "\x1B[41mERROR\x1B[0m"}, // NOSONAR
			{LoggerSeverity::Critical, "\x1B[31;47mCRITICAL\x1B[0m"}}; // NOSONAR
	}

	std::string Logger::FormatLog(const LoggerSeverity &_severity, const std::string _message)
	{
		return std::format("[{}] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] {}", // NOSONAR
						   getSeverityTextAt(_severity), // Put the severity Name
						   doc::threadName,				 // Put the thread Name
						   timeProvider(),				 // Put the time stamp in this format (YYYY-mm-dd HH:MM:SS)
						   _message);					 // Put the message
	}

#pragma endregion

#pragma region Public
#pragma region Constructor

	Logger::Logger(const std::string &_threadName, const LoggerOptions &_options)
	{
		initSeverityMap();

		if (doc::threadName.empty())
			doc::threadName = _threadName;

		lOpts = _options;						// assign the options
		timeProvider = lOpts.getTimeProvider(); // get the time provider from the options

		if (lOpts.isOutputConsole()) // Check if the output in the console is asked
		{
			RegisterOutputStream(&std::cout); // Push it into the vector
		}

		if (lOpts.isOutputFile()) // Check if the output in the file is asked
		{
			if (lOpts.getFileStream()->is_open())			 // check if the file is open
				RegisterOutputStream(lOpts.getFileStream()); // if yes, push it into the vector
			else
				std::cout << FormatLog(LoggerSeverity::Warning, std::format("The file {} can't be open.", lOpts.getFileName())) << std::endl; // Log a warning if the file can't be open
		}
	}

	Logger::Logger(const std::string &_threadName) : Logger(_threadName, *gOpts) {}

	Logger::Logger(const LoggerOptions &_options) : Logger(std::format("{}", std::this_thread::get_id()), _options) {}

	Logger::Logger() : Logger(std::format("{}", std::this_thread::get_id()), *gOpts) {}

#pragma endregion

	void Logger::Log(const LoggerSeverity &_severity, const std::string &_message)
	{

		if (_severity.value < severityThreshold.value) // Check if the severity is beyond the threshold
			return;

		std::lock_guard guard(doc::lock); // lock for avoid access from other thread

		std::string formattedMessage = FormatLog(_severity, _message); // get the message formatted

		for (const auto stream : outputStreams) // browse all the stream
		{
			// send the message, into each stream
			(*stream) << formattedMessage << std::endl;
		}

		for (const auto callback : logCallbacks) // browse all the callbacks
		{
			// call each one of them and give them the formattedMessage
			callback(formattedMessage);
		}
	}

	void Logger::RegisterOutputStream(std::ostream *_stream)
	{
		outputStreams.push_back(_stream);
	}

	void Logger::RegisterLogCallback(std::function<void(const std::string)> _callback)
	{
		logCallbacks.push_back(_callback);
	}

	void Logger::Caller(const std::source_location &where)
	{
		Log(LoggerSeverity::Debug, std::format("{} is called", where.function_name()));
	}

	void Logger::setSeverityThreshdold(const LoggerSeverity &_threshdold)
	{
		severityThreshold = _threshdold;
	}

#pragma endregion
#pragma endregion
}
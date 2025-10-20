#include "./Include/Logger.h"

namespace doc
{
	thread_local std::string threadName = "";

#pragma region rLogger Class
#pragma region Protected

	const std::unordered_map<LoggerSeverity, std::string> &Logger::getSeverityText()
	{
		static const std::unordered_map<LoggerSeverity, std::string> st = {
			{LoggerSeverity::Trace, "TRACE"},
			{LoggerSeverity::Debug, "DEBUG"},
			{LoggerSeverity::Info, "INFO"},
			{LoggerSeverity::Warning, "WARNING"},
			{LoggerSeverity::Error, "ERROR"},
			{LoggerSeverity::Critical, "CRITICAL"}};

		return st;
	}

	const std::unordered_map<LoggerSeverity, std::string> &Logger::getSeverityColor()
	{
		static const std::unordered_map<LoggerSeverity, std::string> sc = {
			{LoggerSeverity::Trace, "\033[35m"},	   // Purple
			{LoggerSeverity::Debug, "\033[34m"},	   // Blue
			{LoggerSeverity::Info, "\033[32m"},		   // Green
			{LoggerSeverity::Warning, "\033[33m"},	   // Yellow
			{LoggerSeverity::Error, "\033[31m"},	   // Red
			{LoggerSeverity::Critical, "\033[97;41m"}, // White on Red
			{LoggerSeverity::None, "\033[0m"}		   // White
		};

		return sc;
	}

	std::string Logger::FormatLog(const LoggerSeverity &_severity, const std::string _message)
	{
		return std::format("| [{}] [{:%Y-%m-%d %H:%M:%S}] [{}] {} |",
						   getSeverityText().at(_severity), // Put the severity Name
						   timeProvider(),					// Put the time stamp in this format (YYYY-mm-dd HH:MM:SS)
						   doc::threadName,					// Put the thread Name
						   _message);						// Put the message
	}

#pragma endregion

#pragma region Public
#pragma region Constructor

	Logger::Logger(const std::string &_threadName, const LoggerOptions &_options)
	{
		if (doc::threadName.empty())
			doc::threadName = _threadName;

		// some dead code for have the thread id in the thread name
		// doc::threadName = std::format("{} ( id : {})", _threadName, std::hash<std::thread::id>{}(std::this_thread::get_id()));

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

	Logger::Logger(const LoggerOptions &_options) : Logger("Main", _options) {}

	Logger::Logger() : Logger("Main", *gOpts) {}

#pragma endregion

	void Logger::Log(const LoggerSeverity &_severity, const std::string &_message)
	{
		PROFILER_TIMER_FUNCTION;

		if (_severity.value < severityThreshdold.value) // Check if the severity is beyond the threshold
			return;

		std::lock_guard guard(doc::lock); // lock for avoid access from other thread

		std::string formattedMessage = FormatLog(_severity, _message); // get the message formatted

		for (const auto stream : outputStreams) // browse all the stream
		{
			// send the message, with its ANSI code for the color, into each stream
			(*stream) << getSeverityColor().at(_severity) << formattedMessage << getSeverityColor().at(LoggerSeverity::None) << std::endl;
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

	void Logger::setSeverityThreshdold(const LoggerSeverity &_severity)
	{
		severityThreshdold = _severity;
	}

#pragma endregion
#pragma endregion
}
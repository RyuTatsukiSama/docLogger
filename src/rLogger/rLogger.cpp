#include "rLogger.h"
using namespace doc; // TODO : delete it when all the logger will be in the namespace

namespace doc
{
	thread_local std::string threadName;
};

#pragma region rLogger Class
#pragma region Protected

const std::unordered_map<rLoggerSeverity, std::string> &rLogger::getSeverityText()
{
	static const std::unordered_map<rLoggerSeverity, std::string> st = {
		{rLoggerSeverity::Trace, "TRACE"},
		{rLoggerSeverity::Debug, "DEBUG"},
		{rLoggerSeverity::Info, "INFO"},
		{rLoggerSeverity::Warning, "WARNING"},
		{rLoggerSeverity::Error, "ERROR"},
		{rLoggerSeverity::Critical, "CRITICAL"}};

	return st;
}

const std::unordered_map<rLoggerSeverity, std::string> &rLogger::getSeverityColor()
{
	static const std::unordered_map<rLoggerSeverity, std::string> sc = {
		{rLoggerSeverity::Trace, "\033[35m"},		// Purple
		{rLoggerSeverity::Debug, "\033[34m"},		// Blue
		{rLoggerSeverity::Info, "\033[32m"},		// Green
		{rLoggerSeverity::Warning, "\033[33m"},		// Yellow
		{rLoggerSeverity::Error, "\033[31m"},		// Red
		{rLoggerSeverity::Critical, "\033[97;41m"}, // White on Red
		{rLoggerSeverity::None, "\033[0m"}			// White
	};

	return sc;
}

std::string rLogger::FormatLog(const rLoggerSeverity &_severity, const std::string _message)
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

rLogger::rLogger(std::string _threadName)
{
	if (doc::threadName == "") // assign the thread name if it's empty
		doc::threadName = _threadName;

	timeProvider = gOpts->getTimeProvider(); // get the time provider from the options

	if (gOpts->isOutputConsole()) // Check if the output in the console is asked
	{
		RegisterOutputStream(&std::cout); // Push it into the vector
	}

	if (gOpts->isOutputFile()) // Check if the output in the file is asked
	{
		if (gOpts->getFileStream()->is_open())			  // check if the file is open
			RegisterOutputStream(gOpts->getFileStream()); // if yes, push it into the vector
		else
			std::cout << FormatLog(rLoggerSeverity::Warning, std::format("The file {} can't be open.", gOpts->getFileName())) << std::endl; // Log a warning if the file can't be open
	}
}

#pragma endregion

void rLogger::Log(const rLoggerSeverity &_severity, const std::string &_message)
{
	if (_severity.value < severityThreshdold.value) // Check if the severity is beyond the threshold
		return;

	std::lock_guard guard(doc::lock); // lock for avoid access from other thread

	std::string formattedMessage = FormatLog(_severity, _message); // get the message formatted

	for (const auto stream : outputStreams) // browse all the stream
	{
		// send the message, with its ANSI code for the color, into each stream
		(*stream) << getSeverityColor().at(_severity) << formattedMessage << getSeverityColor().at(rLoggerSeverity::None) << std::endl;
	}

	for (const auto callback : logCallbacks) // browse all the callbacks
	{
		// call each one of them and give them the formattedMessage
		callback(formattedMessage);
	}
}

void rLogger::RegisterOutputStream(std::ostream *_stream)
{
	outputStreams.push_back(_stream);
}

void rLogger::RegisterLogCallback(std::function<void(const std::string)> _callback)
{
	logCallbacks.push_back(_callback);
}

void rLogger::Caller(const std::source_location &where)
{
	Log(rLoggerSeverity::Debug, std::format("{} is called", where.function_name()));
}

void rLogger::setSeverityThreshdold(const rLoggerSeverity& _severity)
{
	severityThreshdold = _severity;
}

#pragma endregion
#pragma endregion
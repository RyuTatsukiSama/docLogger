#include "rLogger.h"

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
		{rLoggerSeverity::Critical, "\033[97;41m"}, // 244 Red on white or 79 White on Red
		{rLoggerSeverity::None, "\033[0m"}			// White
	};

	return sc;
}

std::string rLogger::FormatLog(const rLoggerSeverity &_severity, const std::string _message)
{
	return std::format("| [{}] [{:%Y-%m-%d %H:%M:%S}] [{}] {} |",
					   getSeverityText().at(_severity),
					   timeProvider(),
					   r::threadName,
					   _message);
}

#pragma endregion

#pragma region Public
#pragma region Constructor

rLogger::rLogger(std::string _threadName)
{
	r::threadName = _threadName;

	timeProvider = gOpts->getTimeProvider();

	if (gOpts->isOutputConsole())
	{
		RegisterOutputStream(&std::cout);
	}

	if (gOpts->isOutputFile())
	{
		if (gOpts->getFileStream()->is_open())
			RegisterOutputStream(gOpts->getFileStream());
		else
			std::cout << FormatLog(rLoggerSeverity::Warning, std::format("The file {} can't be open.", gOpts->getFileName())) << std::endl;
	}
}

#pragma endregion

void rLogger::Log(const rLoggerSeverity &_severity, const std::string &_message) // Color change can be optimise
{
	std::lock_guard guard(r::lock);
	if (_severity.value < severityThreshdold.value)
		return;

	std::string formattedMessage = FormatLog(_severity, _message);

	for (const auto stream : outputStreams)
	{
		(*stream) << getSeverityColor().at(_severity) << formattedMessage << getSeverityColor().at(rLoggerSeverity::None) << std::endl;
	}

	for (const auto callback : logCallbacks)
	{
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
	Log(rLoggerSeverity::Debug, std::format("Called by {}", where.function_name()));
}

#pragma endregion
#pragma endregion
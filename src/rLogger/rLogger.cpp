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
		{rLoggerSeverity::Trace, "\033[35m"},		 // Purple
		{rLoggerSeverity::Debug, "\033[34m"},		 // Blue
		{rLoggerSeverity::Info, "\033[32m"},		 // Green
		{rLoggerSeverity::Warning, "\033[33m"},		 // Yellow
		{rLoggerSeverity::Error, "\033[31m"},		 // Red
		{rLoggerSeverity::Critical, " \033[97;41m"}, // 244 Red on white or 79 White on Red
		{rLoggerSeverity::None, "\033[0m"}			 // White
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

rLogger::rLogger(rLoggerOptions _options)
{
	r::threadName = _options.threadName;

	timeProvider = _options.timeProvider;

	if (_options.outputConsole)
	{
		RegisterOutputStream(&std::cout);
	}

	if (_options.outputFile)
	{
		if (_options.fileName == "")
		{
			std::chrono::time_point now = std::chrono::floor<std::chrono::seconds>(timeProvider());
			_options.fileName = std::format("{:%Y-%m-%d_%H-%M-%S}", now);
		}

		if (!std::filesystem::exists("rLogs"))
		{
			std::filesystem::create_directory("rLogs");
		}

		std::string fileName = std::format("rLogs/{}.log", _options.fileName);
		std::fstream *logFile = new std::fstream(fileName, std::ios::out);

		if (logFile->is_open())
			RegisterOutputStream(logFile);
		else
			std::cout << FormatLog(rLoggerSeverity::Warning, std::format("The file {} can't be open.", fileName)) << std::endl;
	}
}

#pragma endregion

rLogger::~rLogger()
{
	for (const auto stream : outputStreams)
	{
		if (stream != &std::cout)
		{
			delete stream;
		}
	}
}

void rLogger::Log(const rLoggerSeverity &_severity, const std::string &_message) // Color change can be optimise
{
	if (_severity.value < severityThreshdold.value)
		return;

	std::string formattedMessage = FormatLog(_severity, _message);

	for (const auto stream : outputStreams)
	{
		(*stream) << getSeverityColor().at(_severity) << formattedMessage << getSeverityColor().at(rLoggerSeverity::None) << std::endl;
	}
}

void rLogger::RegisterOutputStream(std::ostream *_stream)
{
	outputStreams.push_back(_stream);
}

#pragma endregion
#pragma endregion
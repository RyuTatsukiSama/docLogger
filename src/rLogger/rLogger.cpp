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

const std::unordered_map<rLoggerSeverity, int> &rLogger::getSeverityColor()
{
	static const std::unordered_map<rLoggerSeverity, int> sc = {
		{rLoggerSeverity::Trace, 5},	  // Purple
		{rLoggerSeverity::Debug, 1},	  // Blue
		{rLoggerSeverity::Info, 2},		  // Green
		{rLoggerSeverity::Warning, 6},	  // Yellow
		{rLoggerSeverity::Error, 4},	  // Red
		{rLoggerSeverity::Critical, 244}, // Red on white
		{rLoggerSeverity::None, 7}		  // White
	};

	return sc;
}

std::string rLogger::FormatLog(const rLoggerSeverity &_severity, const std::string _message)
{
	return std::format("[{}] [{}] [{}] {}", getSeverityText().at(_severity), std::chrono::system_clock::now(), threadName, _message);
}

#pragma endregion

#pragma region Public
#pragma region Constructor

rLogger::rLogger(std::string _threadName)
{
	threadName = _threadName;
}

rLogger::rLogger(rLoggerOptions _options)
{
	threadName = _options.threadName;

	if (_options.outputConsole)
	{
		RegisterOutputStream(&std::cout);
	}

	if (_options.outputFile)
	{
		if (_options.fileName == "")
		{
			std::chrono::time_point now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
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
		if (stream == &std::cout)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hConsole, getSeverityColor().at(_severity));

			(*stream) << formattedMessage << std::endl;

			SetConsoleTextAttribute(hConsole, getSeverityColor().at(rLoggerSeverity::None)); // reset to white
		}
		else
			(*stream) << formattedMessage << std::endl;
	}
}

void rLogger::RegisterOutputStream(std::ostream *_stream)
{
	outputStreams.push_back(_stream);
}

#pragma endregion
#pragma endregion
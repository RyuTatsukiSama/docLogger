#include "rLogger.h"

const rLoggerSeverity rLoggerSeverity::Log = rLoggerSeverity(0);
const rLoggerSeverity rLoggerSeverity::Debug = rLoggerSeverity(1);
const rLoggerSeverity rLoggerSeverity::Info = rLoggerSeverity(2);
const rLoggerSeverity rLoggerSeverity::Warning = rLoggerSeverity(3);
const rLoggerSeverity rLoggerSeverity::Error = rLoggerSeverity(4);
const rLoggerSeverity rLoggerSeverity::Critical = rLoggerSeverity(5);

#pragma region rLogger Class
#pragma region Protected

std::unordered_map<int, std::string> rLogger::severityText = {
	{rLoggerSeverity::Log.value, "LOG"},
	{rLoggerSeverity::Debug.value, "DEBUG"},
	{rLoggerSeverity::Info.value, "INFO"},
	{rLoggerSeverity::Warning.value, "WARNING"},
	{rLoggerSeverity::Error.value, "ERROR"},
	{rLoggerSeverity::Critical.value, "CRITICAL"}};

std::string rLogger::FormatLog(const rLoggerSeverity &_severity, const std::string _message)
{
	return std::format("[{}] [{}] [{}] {}", severityText.at(_severity.value), std::chrono::system_clock::now(), threadName, _message);
}

void rLogger::ColorConsole(const rLoggerSeverity &_severity)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int consoleColor = 7; // White

	switch (_severity.value)
	{
	case 3:				  // WARNING
		consoleColor = 6; // Yellow
		break;
	case 4:				  // ERROR
		consoleColor = 4; // Red
		break;
	case 5:				   // CRITICAL
		consoleColor = 12; // bright red
		break;
	default:
		break;
	}

	SetConsoleTextAttribute(hConsole, consoleColor);
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

		std::fstream *logFile = new std::fstream(std::format("{}.log", _options.fileName), std::ios::out);

		if (logFile->is_open())
			RegisterOutputStream(logFile);
		else
			std::cout << FormatLog(rLoggerSeverity::Warning, std::format("The file {} can't be open.", _options.fileName));
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

	bool consoleColorChanged = false;
	for (const auto stream : outputStreams)
	{
		if (stream == &std::cout && _severity.value > rLoggerSeverity::Info.value)
		{
			ColorConsole(_severity);
			consoleColorChanged = true;
		}

		(*stream) << formattedMessage << std::endl;

		if (consoleColorChanged)
			ColorConsole(rLoggerSeverity::Log); // Us this to reset the color of the console to white
	}
}

void rLogger::RegisterOutputStream(std::ostream *_stream)
{
	outputStreams.push_back(_stream);
}

#pragma endregion
#pragma endregion
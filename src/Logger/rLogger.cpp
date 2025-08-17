#include "rLogger.h"

const rLogSeverity rLogSeverity::Log = rLogSeverity(0);
const rLogSeverity rLogSeverity::Debug = rLogSeverity(1);
const rLogSeverity rLogSeverity::Info = rLogSeverity(2);
const rLogSeverity rLogSeverity::Warning = rLogSeverity(3);
const rLogSeverity rLogSeverity::Error = rLogSeverity(4);
const rLogSeverity rLogSeverity::Critical = rLogSeverity(5);

#pragma region rLogger Class
#pragma region Protected

std::unordered_map<int, std::string> rLogger::severityText = {
	{rLogSeverity::Log.value, "LOG"},
	{rLogSeverity::Debug.value, "DEBUG"},
	{rLogSeverity::Info.value, "INFO"},
	{rLogSeverity::Warning.value, "WARNING"},
	{rLogSeverity::Error.value, "ERROR"},
	{rLogSeverity::Critical.value, "CRITICAL"}};

std::string rLogger::FormatLog(const rLogSeverity &_severity, const std::string _message)
{
	return std::format("[{}] [{}] [{}] {}", severityText.at(_severity.value), std::chrono::system_clock::now(), threadName, _message);
}

void rLogger::ColorConsole(const rLogSeverity &_severity)
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

rLogger::rLogger(std::string _threadName)
{
	threadName = _threadName;

	RegisterOutputStream(&std::cout);
}

void rLogger::Log(const rLogSeverity &_severity, const std::string &_message) // Color change can be optimise
{
	if (_severity.value < severityThreshdold.value)
		return;

	std::string formattedMessage = FormatLog(_severity, _message);

	bool consoleColorChanged = false;
	for (const auto stream : outputStreams)
	{
		if (stream == &std::cout && _severity.value > rLogSeverity::Info.value)
		{
			ColorConsole(_severity);
			consoleColorChanged = true;
		}

		(*stream) << formattedMessage << std::endl;

		if (consoleColorChanged)
			ColorConsole(rLogSeverity::Log); // Us this to reset the color of the console to white
	}
}

void rLogger::RegisterOutputStream(std::ostream *_stream)
{
	outputStreams.push_back(_stream);
}

#pragma endregion
#pragma endregion
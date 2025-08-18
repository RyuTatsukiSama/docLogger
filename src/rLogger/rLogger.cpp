#include "rLogger.h"

const rLoggerSeverity rLoggerSeverity::Trace = rLoggerSeverity{0};
const rLoggerSeverity rLoggerSeverity::Debug = rLoggerSeverity{1};
const rLoggerSeverity rLoggerSeverity::Info = rLoggerSeverity{2};
const rLoggerSeverity rLoggerSeverity::Warning = rLoggerSeverity{3};
const rLoggerSeverity rLoggerSeverity::Error = rLoggerSeverity{4};
const rLoggerSeverity rLoggerSeverity::Critical = rLoggerSeverity{5};
const rLoggerSeverity rLoggerSeverity::None = rLoggerSeverity{6};

#pragma region rLogger Class
#pragma region Protected

std::unordered_map<int, std::string> rLogger::severityText = {
	{rLoggerSeverity::Trace.value, "TRACE"},
	{rLoggerSeverity::Debug.value, "DEBUG"},
	{rLoggerSeverity::Info.value, "INFO"},
	{rLoggerSeverity::Warning.value, "WARNING"},
	{rLoggerSeverity::Error.value, "ERROR"},
	{rLoggerSeverity::Critical.value, "CRITICAL"}};

std::unordered_map<int, int> rLogger::severityColor = {
	{rLoggerSeverity::Trace.value, 5},		// Purple
	{rLoggerSeverity::Debug.value, 1},		// Blue
	{rLoggerSeverity::Info.value, 2},		// Green
	{rLoggerSeverity::Warning.value, 6},	// Yellow
	{rLoggerSeverity::Error.value, 4},		// Red
	{rLoggerSeverity::Critical.value, 244}, // Red on white
	{rLoggerSeverity::None.value, 7}		// White
};

std::string rLogger::FormatLog(const rLoggerSeverity &_severity, const std::string _message)
{
	return std::format("[{}] [{}] [{}] {}", severityText.at(_severity.value), std::chrono::system_clock::now(), threadName, _message);
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

			SetConsoleTextAttribute(hConsole, severityColor.at(_severity.value));

			(*stream) << formattedMessage << std::endl;

			SetConsoleTextAttribute(hConsole, severityColor.at(rLoggerSeverity::None.value)); // reset to white
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
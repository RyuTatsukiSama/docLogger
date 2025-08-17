#include "rLogger.h"

const rLogSeverity rLogSeverity::LOG = rLogSeverity(0);
const rLogSeverity rLogSeverity::DEBUG = rLogSeverity(1);
const rLogSeverity rLogSeverity::INFO = rLogSeverity(2);
const rLogSeverity rLogSeverity::WARNING = rLogSeverity(3);
const rLogSeverity rLogSeverity::ERROR = rLogSeverity(4);
const rLogSeverity rLogSeverity::CRITICAL = rLogSeverity(5);

#pragma region rLogger Class
#pragma region Protected

std::unordered_map<rLogSeverity, std::string> rLogger::severityText = {
    {rLogSeverity::LOG, "LOG"},
    {rLogSeverity::DEBUG, "DEBUG"},
    {rLogSeverity::INFO, "INFO"},
    {rLogSeverity::WARNING, "WARNING"},
    {rLogSeverity::ERROR, "ERROR"},
    {rLogSeverity::CRITICAL, "CRITICAL"}};

std::string rLogger::FormatLog(const rLogSeverity &_severity, const std::string _message)
{
    return std::format("[{}] [{}] [{}] {}", severityText.at(_severity), threadName, time(NULL), _message);
}

void rLogger::ColorConsole(const rLogSeverity &_severity)
{
}

#pragma endregion

#pragma region Public

rLogger::rLogger(std::string _threadName)
{
    threadName = _threadName;

    outputStreams.push_back(&std::cout);
}

void rLogger::Log(const rLogSeverity &_severity, const std::string &_message)
{
    if (_severity.value < severityThreshdold.value)
        return;

    std::string_view formattedMessage = FormatLog(_severity, _message);

    for (auto os : outputStreams)
        (*os) << formattedMessage << std::endl;
}

void rLogger::RegisterOutputStream(const std::ofstream &_stream)
{
}

#pragma endregion
#pragma endregion
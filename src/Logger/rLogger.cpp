#include "rLogger.h"

const rLogSeverity rLogSeverity::LOG = rLogSeverity(0);
const rLogSeverity rLogSeverity::DEBUG = rLogSeverity(1);
const rLogSeverity rLogSeverity::INFO = rLogSeverity(2);
const rLogSeverity rLogSeverity::WARNING = rLogSeverity(3);
const rLogSeverity rLogSeverity::ERROR = rLogSeverity(4);
const rLogSeverity rLogSeverity::CRITICAL = rLogSeverity(5);

#pragma region rLogger Class
#pragma region Protected Methods

std::string rLogger::FormatLog(const rLogSeverity &_severity, const std::string _message)
{
    return "";
}

#pragma endregion

#pragma region Public Methods

rLogger::rLogger(std::string _threadName)
{
}

void rLogger::Log(const rLogSeverity &_severity, const std::string &_message)
{
}

void rLogger::RegisterOutputStream(const std::ofstream &_stream)
{
}

#pragma endregion
#pragma endregion
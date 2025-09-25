#include "rLogger.h"

void rLogger::Trace(const std::string &_message)
{
    Log(rLoggerSeverity::Trace, _message);
}

void rLogger::Debug(const std::string &_message)
{
    Log(rLoggerSeverity::Debug, _message);
}

void rLogger::Info(const std::string &_message)
{
    Log(rLoggerSeverity::Info, _message);
}

void rLogger::Warning(const std::string &_message)
{
    Log(rLoggerSeverity::Warning, _message);
}

void rLogger::Error(const std::string &_message)
{
    Log(rLoggerSeverity::Error, _message);
}

void rLogger::Critical(const std::string &_message)
{
    Log(rLoggerSeverity::Critical, _message);
}
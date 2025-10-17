#include "rLogger.h"

namespace doc
{
    void Logger::Trace(const std::string &_message)
    {
        Log(LoggerSeverity::Trace, _message);
    }
    
    void Logger::Debug(const std::string &_message)
    {
        Log(LoggerSeverity::Debug, _message);
    }
    
    void Logger::Info(const std::string &_message)
    {
        Log(LoggerSeverity::Info, _message);
    }
    
    void Logger::Warning(const std::string &_message)
    {
        Log(LoggerSeverity::Warning, _message);
    }
    
    void Logger::Error(const std::string &_message)
    {
        Log(LoggerSeverity::Error, _message);
    }
    
    void Logger::Critical(const std::string &_message)
    {
        Log(LoggerSeverity::Critical, _message);
    }
}
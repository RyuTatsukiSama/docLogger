#include "./Include/LoggerSeverity.h"
namespace doc
{
    const LoggerSeverity LoggerSeverity::Trace = LoggerSeverity{0};
    const LoggerSeverity LoggerSeverity::Debug = LoggerSeverity{1};
    const LoggerSeverity LoggerSeverity::Info = LoggerSeverity{2};
    const LoggerSeverity LoggerSeverity::Warning = LoggerSeverity{3};
    const LoggerSeverity LoggerSeverity::Error = LoggerSeverity{4};
    const LoggerSeverity LoggerSeverity::Critical = LoggerSeverity{5};
    const LoggerSeverity LoggerSeverity::None = LoggerSeverity{6};
} 
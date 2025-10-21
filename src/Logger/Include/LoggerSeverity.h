#ifndef RLOGGERSEVERITY_H
#define RLOGGERSEVERITY_H

#include <iostream>
#include "DLL_API.h"

namespace doc
{
    /// @brief Severity levels for the logger
    struct DLL_API LoggerSeverity
    {
        int value;

        static const LoggerSeverity Trace;
        static const LoggerSeverity Debug;
        static const LoggerSeverity Info;
        static const LoggerSeverity Warning;
        static const LoggerSeverity Error;
        static const LoggerSeverity Critical;
        static const LoggerSeverity None;
    };

    /// @brief Compare two LoggerSeverity
    inline DLL_API bool operator==(const LoggerSeverity &_s1, const LoggerSeverity &_s2)
    {
        return _s1.value == _s2.value;
    }

}
namespace std
{
    /// @brief Hash function for LoggerSeverity to use it in unordered_map
    template <>
    struct hash<doc::LoggerSeverity>
    {
        size_t operator()(const doc::LoggerSeverity &_severity) const
        {
            return hash<int>{}(_severity.value);
        }
    };
}

#endif // !RLOGGERSEVERITY_H
#ifndef RLOGGERSEVERITY_H
#define RLOGGERSEVERITY_H

#include <iostream>
namespace doc
{
    /// @brief Severity levels for the logger
    struct LoggerSeverity
    {
        int value;

        static const LoggerSeverity Trace, Debug, Info, Warning, Error, Critical, None;
    };

    /// @brief Compare two LoggerSeverity
    inline bool operator==(const LoggerSeverity &_s1, const LoggerSeverity &_s2)
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
#ifndef RLOGGERSEVERITY_H
#define RLOGGERSEVERITY_H

#ifndef DOC_LOG_THRESHOLD
#define DOC_LOG_THRESHOLD rLoggerSeverity::Trace
#endif

#include <iostream>

struct rLoggerSeverity
{
    int value;

    static const rLoggerSeverity Trace, Debug, Info, Warning, Error, Critical, None;
};

inline bool operator==(const rLoggerSeverity& _s1, const rLoggerSeverity& _s2)
{
    return _s1.value == _s2.value;
}

namespace std
{
    template <>
    struct hash<rLoggerSeverity>
    {
        size_t operator()(const rLoggerSeverity& _severity) const
        {
            return hash<int>{}(_severity.value);
        }
    };
}

#endif // !RLOGGERSEVERITY_H
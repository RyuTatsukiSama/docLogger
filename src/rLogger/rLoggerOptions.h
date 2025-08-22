#ifndef RLOGGEROPTIONS_H
#define RLOGGEROPTIONS_H

#include <string>

typedef struct rLoggerOptions
{
    std::string threadName;
    bool outputConsole;
    bool outputFile;
    std::string fileName;

    struct defaults_t
    {
        std::string threadName = "Main";
        bool outputConsole = true;
        bool outputFile = true;
        std::string fileName = "";

        operator rLoggerOptions() const
        {
            return rLoggerOptions{threadName, outputConsole, outputFile, fileName};
        };
    };

    static inline const defaults_t defaults{};
} rLoggerOptions;

#endif // !RLOGGEROPTIONS_H
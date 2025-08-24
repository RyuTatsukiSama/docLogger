#ifndef RLOGGEROPTIONS_H
#define RLOGGEROPTIONS_H

#include <string>
#include <functional>
#include <chrono>

typedef struct rLoggerOptions
{
    std::string threadName;
    bool outputConsole;
    bool outputFile;
    std::string fileName;
    std::function<std::chrono::system_clock::time_point()> timeProvider;

    struct defaults_t
    {
        std::string threadName = "Main";
        bool outputConsole = true;
        bool outputFile = true;
        std::string fileName = "";
        std::function<std::chrono::system_clock::time_point()> timeProvider = []()
        { return std::chrono::zoned_time{
              std::chrono::current_zone(),
              std::chrono::system_clock::now()}; };

        operator rLoggerOptions() const
        {
            return rLoggerOptions{threadName, outputConsole, outputFile, fileName, timeProvider};
        };
    };

    static inline const defaults_t defaults{};
    static rLoggerOptions make(defaults_t d) { return d; } // ! Get a better Name
} rLoggerOptions;

#endif // !RLOGGEROPTIONS_H
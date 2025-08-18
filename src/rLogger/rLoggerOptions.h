#ifndef RLOGGEROPTIONS_H
#define RLOGGEROPTIONS_H

#include <string>

typedef struct rLoggerOptions
{
    std::string threadName = "Main";
    bool outputConsole = true;
    bool outputFile = true;
    std::string fileName = "";
} rLoggerOptions;

#endif // !RLOGGEROPTIONS_H